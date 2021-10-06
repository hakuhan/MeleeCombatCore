#include "TargetSystem/TargetSystem.h"
#include "Components/SphereComponent.h"

void UTargetSystem::BeginPlay()
{
    if (!m_IsUpdatedInfo && !m_InfoTable.IsNull())
    {
        auto targetInfoPtr = m_InfoTable.GetRow<FTargetInfo>("Find target info");
        m_Info = *targetInfoPtr;
        m_Data.Reset();
    }
}

void UTargetSystem::UpdateInfo(const FTargetInfo &info)
{
    m_IsUpdatedInfo = true;
    m_Info = info;
    m_Data.Reset();
}

void UTargetSystem::SwitchTarget()
{
    if (m_CheckingComponent && m_CheckingComponent->IsActive())
    {
        return;
    }

    m_Data.AvailableTargets.Empty();

    // Find target by range
    if (!m_CheckingComponent)
    {
        m_CheckingComponent = NewObject<USphereComponent>(this, USphereComponent::StaticClass());
        // Base info
        m_CheckingComponent->SetVisibility(m_bDebug);
        m_CheckingComponent->SetHiddenInGame(!m_bDebug);
        if (m_bDebug)
        {
            m_CheckingComponent->ShapeColor = FColor::Green;
        }

        m_CheckingComponent->SetWorldLocation(GetOwner()->GetActorLocation());
        m_CheckingComponent->bShouldCollideWhenPlacing = true;
        m_CheckingComponent->InitSphereRadius(m_Info.DetectRadius * 100);
        m_CheckingComponent->SetCollisionProfileName(m_Info.CollisionPresetName);
        m_CheckingComponent->OnComponentBeginOverlap.AddDynamic(this, &UTargetSystem::OnOverlabBegin);
        m_CheckingComponent->RegisterComponent();
        m_CheckingComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
    }
    else
    {
        m_CheckingComponent->SetActive(true);
        m_CheckingComponent->SetSphereRadius(m_Info.DetectRadius * 100);
    }

    FTimerHandle handle;
    GetOwner()->GetWorld()->GetTimerManager().SetTimer(
        handle, [&]
        {
            if (m_bDebug)
            {
                FString _allTargets;
                for (auto _actor : m_Data.AvailableTargets)
                {
                    if (_actor)
                    {
                        _allTargets += _actor->GetName() + ",";
                    }
                }
                UE_LOG(LogTemp, Error, TEXT("All targets: %s"), *_allTargets)
            }

            m_CheckingComponent->SetActive(false);
            m_CheckingComponent->SetSphereRadius(0);

            // Find best target
            AActor *target = FindBestTarget(m_Data.AvailableTargets);
            if (target)
            {
                m_Data.CurrentTarget = target;
                m_OnSeleteTarget.Broadcast(GetOwner(), target);
                if (m_bDebug)
                {
                    UE_LOG(LogTemp, Error, TEXT("Best target is: %s"), *(target->GetName()))
                }

                // Switch target behavior
                switch (m_Info.SwitchingRule)
                {
                case ESwitchToRule::TARGET_LockAndFaceTo:
                    FaceToTarget();
                case ESwitchToRule::TARGET_Lock:
                    LockOnTarget();
                    break;

                case ESwitchToRule::TARGET_LookAtAndFaceTo:
                    FaceToTarget();
                case ESwitchToRule::TARGET_LookAt:
                    LookAtTarget();
                    break;
                default:
                    UE_LOG(LogTemp, Error, TEXT("Rule not implemented!"))
                    break;
                }
            }
        },
        m_Info.m_CheckingDuration, false);
}

AActor *UTargetSystem::FindBestTarget_Implementation(const TArray<AActor *> &avaliables)
{
    if (avaliables.Num() == 0)
    {
        return nullptr;
    }

    struct AvaliableTargetInfo
    {
        AActor *Target;
        FVector Position;
        float Angle;
        float RelativeDistance;
        float RelativeHight;
    };

    // Checking range lambda
    auto CheckTargetRangeLambda = [&](float _pointAngle, float _range, float _maxDistance, const AvaliableTargetInfo &_targetInfo)
    {
        float _minAngle = _pointAngle - _range;
        float _maxAngle = _pointAngle + _range;
        // if coss 180 digree. condition must reverse because range is from -180 to 180
        bool _cross = false;
        if (_minAngle < -180)
        {
            _cross = true;
            _minAngle = _maxAngle;
            _maxAngle = (int)(-_pointAngle + _range) % 180;
        }
        else if (_maxAngle > 180)
        {
            _cross = true;
            _maxAngle = _minAngle;
            _minAngle = ((int)(_pointAngle + _range) % 180) * -1;
        }

        bool _withinRange = false;
        if (_cross)
        {
            if (_targetInfo.Angle < _minAngle && _targetInfo.Angle > _maxAngle)
            {
                _withinRange = true;
            }
        }
        else if (_targetInfo.Angle > _minAngle && _targetInfo.Angle <= _maxAngle)
        {
            _withinRange = true;
        }

        // check with distance
        bool _result = false;
        if (_withinRange && _maxDistance < _targetInfo.RelativeDistance)
        {
            _result = true;
        }

        return _result;
    };

    // Find best rule
    auto CompareBestTargetLambda = [&](const AvaliableTargetInfo &newTargetInfo, const AvaliableTargetInfo &curTargetInfo, float targetAnglePoint, EBestFindingTagetRule rule)
    {
        bool _result = false;
        // check conditions
        float _preDistancePoint = 0;
        float _curDistancePoint = 0;
        float _preAnglePoint = 0;
        float _curAnglePoint = 0;
        if (rule != EBestFindingTagetRule::FIND_DistanceFirst && rule != EBestFindingTagetRule::FIND_AngleFirst)
        {
            _preDistancePoint = curTargetInfo.RelativeDistance * m_Info.DistanceWeight;
            _curDistancePoint = newTargetInfo.RelativeDistance * m_Info.DistanceWeight;
            // Angle more and point less
            _preAnglePoint = -FMath::Abs(curTargetInfo.Angle - targetAnglePoint) * m_Info.AngleWeight;
            _curAnglePoint = -FMath::Abs(newTargetInfo.Angle - targetAnglePoint) * m_Info.AngleWeight;
        }

        switch (rule)
        {
        case EBestFindingTagetRule::FIND_DistanceFirst:
            if (newTargetInfo.RelativeDistance < curTargetInfo.RelativeDistance)
            {
                _result = true;
            }
            break;

        case EBestFindingTagetRule::FIND_AngleFirst:
            if (FMath::Abs(newTargetInfo.Angle - targetAnglePoint) < FMath::Abs(curTargetInfo.Angle - targetAnglePoint))
            {
                _result = true;
            }
            break;

        case EBestFindingTagetRule::FIND_Banace:
            if ((_preDistancePoint + _preAnglePoint) < (_curDistancePoint + _curAnglePoint))
            {
                _result = true;
            }
            break;

        case EBestFindingTagetRule::FIND_DistanceGold:
            if ((_preDistancePoint * 0.618 + _preAnglePoint * 0.32) < (_curDistancePoint * 0.618 + _curAnglePoint * 0.32))
            {
                _result = true;
            }

            break;

        case EBestFindingTagetRule::FIND_AngleGold:
            if ((_preDistancePoint * 0.32 + _preAnglePoint * 0.618) < (_curDistancePoint * 0.32 + _curAnglePoint * 0.618))
            {
                _result = true;
            }
            break;

        default:
            UE_LOG(LogTemp, Error, TEXT("Find target rule type invalid!"))
            break;
        }

        return _result;
    };

    // Find all target's position and angle
    TArray<AvaliableTargetInfo> targetInfos;
    FVector forwardVector = GetOwner()->GetActorForwardVector();
    FVector ownerLocation = GetOwner()->GetActorLocation();
    for (auto _target : avaliables)
    {
        AvaliableTargetInfo _info;
        _info.Target = _target;
        _info.Position = _target->GetActorLocation();
        FVector _relationVector = _info.Position - forwardVector;
        FVector _relativeVectorNormalize = _relationVector.GetSafeNormal();
        _info.Angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forwardVector, _relativeVectorNormalize)));
        _info.RelativeDistance = _relationVector.Size();
        _info.RelativeHight = ownerLocation.Z - _info.Position.Z;

        targetInfos.Add(_info);
    }

    // Check danger positions
    AActor* dangerousActor = nullptr;
    int dangerousIndex = 0;
    for (float _dangerPointAngle : m_Info.DangerousPoints)
    {
        for (int i = 0; i < targetInfos.Num(); ++i)
        {
            bool _isInRange = CheckTargetRangeLambda(_dangerPointAngle, m_Info.DangerousAngleRange, m_Info.DangerousDistance, targetInfos[i]);

            if (_isInRange && CompareBestTargetLambda(targetInfos[i], targetInfos[dangerousIndex], _dangerPointAngle, m_Info.BestTargetRule))
            {
                dangerousIndex = i;
                dangerousActor = targetInfos[i].Target;
            }
        }
    }
    if (dangerousActor)
    {
        return dangerousActor;
    }

    // Check Pre target
    if (m_Info.bPreTargetFirst && m_Data.CurrentTarget)
    {
        int _preTargetIndex = targetInfos.IndexOfByPredicate([&](const AvaliableTargetInfo &_target)
                                                             { return _target.Target == m_Data.CurrentTarget; });
        if (_preTargetIndex >= 0 && CheckTargetRangeLambda(0, m_Info.FocusRange, m_Info.FocusDistance, targetInfos[_preTargetIndex]))
        {
            return targetInfos[_preTargetIndex].Target;
        }
    }

    // Check focus range
    AActor* focusingActor = nullptr;
    int focusIndex = 0;
    for (int i = 0; i < targetInfos.Num(); ++i)
    {
        bool _isInRange = CheckTargetRangeLambda(0, m_Info.FocusRange, m_Info.FocusDistance, targetInfos[i]);
        if (_isInRange)
        {
            if (_isInRange && CompareBestTargetLambda(targetInfos[i], targetInfos[focusIndex], 0, m_Info.BestTargetRule))
            {
                focusIndex = i;
                focusingActor = targetInfos[i].Target;
            }
        }
        
    }
    if (focusingActor)
    {
        return focusingActor;
    }
    
    // Check Rest targets
    AActor* restBestActor = nullptr;
    int restIndex = 0;
    for (int i = 0; i < targetInfos.Num(); ++i)
    {
        if (CompareBestTargetLambda(targetInfos[i], targetInfos[restIndex], 0, EBestFindingTagetRule::FIND_DistanceFirst))
        {
            restIndex = i;
            restBestActor = targetInfos[i].Target;
        }
    }

    return restBestActor;
}

void UTargetSystem::OnOverlabBegin(class UPrimitiveComponent *Comp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    bool isTarget = false;
    for (auto _tag : OtherActor->Tags)
    {
        if (m_Info.TargetTags.Contains(_tag))
        {
            isTarget = true;
            break;
        }
    }

    if (isTarget)
    {
        m_Data.AvailableTargets.Add(OtherActor);
    }
}

bool UTargetSystem::LockOnTarget_Implementation()
{
    return true;
}

bool UTargetSystem::LookAtTarget_Implementation()
{
    return true;
}

bool UTargetSystem::FaceToTarget_Implementation()
{
    return true;
}
