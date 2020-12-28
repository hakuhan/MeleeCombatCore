#include "AnimNotify/MeleeStopMoving.h"

void UMeleeStopMoving::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
    {
        return;
    }

    UpdateMoveState(MeshComp->GetOwner(), false);
}

void UMeleeStopMoving::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
    {
        return;
    }

    UpdateMoveState(MeshComp->GetOwner(), true);
}

void UMeleeStopMoving::UpdateMoveState(AActor *actor, bool canMove)
{
    TArray<UObject *> _moveOjbs;
    UMeleeUtils::GetImplementFromActor(actor, UCombatMoveInterface::StaticClass(), _moveOjbs);
    if (_moveOjbs.Num() > 0)
    {
        for (auto inputObj : _moveOjbs)
        {
            ICombatMoveInterface::Execute_UpdateMoveState(inputObj, canMove);
        }
    }
    _moveOjbs.Empty();
}