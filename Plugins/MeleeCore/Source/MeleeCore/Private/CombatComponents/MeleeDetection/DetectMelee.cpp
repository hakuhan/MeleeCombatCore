// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeDetection/DetectMelee.h"

// Sets default values for this component's properties
UDetectMelee::UDetectMelee()
{
	PrimaryComponentTick.bCanEverTick = true;
	m_IsDetecting = false;
	m_IsShowTrace = false;
	m_Channel = ECollisionChannel::ECC_GameTraceChannel1;
}

void UDetectMelee::BeginDestroy()
{
	Super::BeginDestroy();
	m_MeleeWeapons.Empty();
	m_HitActorTemps.Empty();
}

// Called when the game starts
void UDetectMelee::BeginPlay()
{
	Super::BeginPlay();

	UpdateWeapon();

	// init solution data
	auto solutionInfo = m_CombatSolutionTable.GetRow<FCombatSolutionTable>("Find combat solution");
	if (solutionInfo != nullptr)
	{
		m_DefaultSolution = solutionInfo->solutionType;

		auto dealObj = NewObject<UObject>(this, solutionInfo->solutionClass);
		auto hurtInfo = solutionInfo->hurtTable.GetRow<FHurt>("Find combat hurt");
		if (dealObj && hurtInfo)
		{
			m_CombatSolution.SetObject(dealObj);
			m_CombatSolution.SetInterface(Cast<ICombatSolution>(dealObj));
			m_CombatSolution->Init(*hurtInfo);

			// set defaul data
			m_DefaultHurt = hurtInfo->hurtType;
		}
	}

	m_EffectComponent = Cast<UMeleeEffect>(GetOwner()->GetComponentByClass(UMeleeEffect::StaticClass()));
}

void UDetectMelee::UpdateHurts(EMeleeHurt newHurt, EDetectionSolution newSolution)
{
	if (m_CombatSolution == nullptr)
	{
		return;
	}

	FCombatSolutionTable *solutionInfo = m_CombatSolutionTable.GetRow<FCombatSolutionTable>("Find combat solution");
	if (newSolution != m_SolutionType)
	{
		for (auto solutionName : m_CombatSolutionTable.DataTable->GetRowNames())
		{
			auto sRow = m_CombatSolutionTable.DataTable->FindRow<FCombatSolutionTable>(solutionName, "Find combat solution", true);
			if (sRow->solutionType == newSolution)
			{
				solutionInfo = sRow;
				auto solutionObj = NewObject<UObject>(this, sRow->solutionClass);
				m_CombatSolution.SetObject(solutionObj);
				m_CombatSolution.SetInterface(Cast<ICombatSolution>(solutionObj));
				m_SolutionType = newSolution;
				break;
			}
		}
	}

	if (newHurt != m_HurtType)
	{
		FHurt newHurtInfo = m_CombatSolution->m_HurtInfo;
		auto hurtTable = solutionInfo->hurtTable.DataTable;
		if (!hurtTable)
		{
			UE_LOG(LogTemp, Error, TEXT("Hurt tale empty!"));
		}
		for (auto name : hurtTable->GetRowNames())
		{
			auto row = hurtTable->FindRow<FHurt>(name, "Find combat hurts", true);
			if (row->hurtType == newHurt)
			{
				newHurtInfo = *row;
				m_HurtType = newHurt;
				break;
			}
		}

		m_CombatSolution->UpdateHurts(newHurtInfo);
	}
}

void UDetectMelee::UpdateHurtRate(float rate)
{
	if (m_CombatSolution != nullptr)
	{
		m_CombatSolution->UpdateHurtRate(rate);
	}
}

void UDetectMelee::UpdateWeaponMask(uint8 weaponMask)
{
	m_WeaponMask = weaponMask;
}

void UDetectMelee::ResetHurts()
{
	UpdateHurts(m_DefaultHurt, m_DefaultSolution);
}

// Called every frame
void UDetectMelee::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	m_HitActorTemps.Empty();
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_IsDetecting)
	{
		auto channel = UEngineTypes::ConvertToTraceType(m_Channel);
		auto debugTraceType = m_IsShowTrace ? EDrawDebugTrace::Type::ForDuration : EDrawDebugTrace::Type::None;

		// attack check
		for (int i = 0; i < m_MeleeWeapons.Num(); ++i)
		{
			if (!m_MeleeWeapons[i]->IsTargetWeapon(m_WeaponMask))
			{
				continue;
			}

			// Get weapon info and data
			if (!m_MeleeWeapons[i]->GetInfo(m_WeaponInfoTemp))
			{
				continue;
			}
			if (!m_MeleeWeapons[i]->GetData(m_WeaponDataTemp))
			{
				continue;
			}

			for (int j = 0; j < m_WeaponInfoTemp.SocketNames.Num(); ++j)
			{
				// 1. Check every single socket
				// check slot location cache
				FVector crtLocation = m_MeleeWeapons[i]->GetDetectLocation(m_WeaponInfoTemp.SocketNames[j]);
				if (m_WeaponDataTemp.TempSocketLocation.Num() <= j)
				{
					m_WeaponDataTemp.TempSocketLocation.Add(crtLocation);
				}
				FVector preLocation = m_WeaponDataTemp.TempSocketLocation[j];

				auto world = GetOwner()->GetWorld();
				m_Hits.Empty();
				UKismetSystemLibrary::LineTraceMulti(world, preLocation, crtLocation, channel, true, m_IgnoreActors, debugTraceType, m_Hits, true, m_TraceColor, m_HittedColor);
				for (auto hit : m_Hits)
				{
					ExecuteHit(hit);
				}

				// 2. Check trace between sokets
				int k = j + 1;
				if (k < m_WeaponInfoTemp.SocketNames.Num())
				{
					auto nextSocketLocation = m_MeleeWeapons[i]->GetDetectLocation(m_WeaponInfoTemp.SocketNames[k]);
					m_Hits.Empty();
					UKismetSystemLibrary::LineTraceMulti(world, crtLocation, nextSocketLocation, channel, true, m_IgnoreActors, debugTraceType, m_Hits, true, m_TraceColor, m_HittedColor);

					for (auto h : m_Hits)
					{
						ExecuteHit(h);
					}
				}

				m_WeaponDataTemp.TempSocketLocation[j] = crtLocation;
			}

			// Update data
			m_MeleeWeapons[i]->SetData(m_WeaponDataTemp);
		}
	}
}

void UDetectMelee::StartDetection()
{
	if (m_CombatSolution != nullptr)
	{
		ICombatSolution::Execute_OnStartDetection(m_CombatSolution.GetObject());
	}
	m_IsDetecting = true;

	ResetData();
}

void UDetectMelee::ResetData()
{
	for (int i = 0; i < m_MeleeWeapons.Num(); ++i)
	{
		if (!m_MeleeWeapons[i]->GetData(m_WeaponDataTemp))
		{
			continue;
		}
		m_WeaponDataTemp.TempSocketLocation.Empty();
		m_MeleeWeapons[i]->SetData(m_WeaponDataTemp);
	}
	if (m_EffectComponent)
	{
		m_EffectComponent->ResetData();
	}
}

void UDetectMelee::EndDetection()
{
	if (m_CombatSolution != nullptr)
	{
		ICombatSolution::Execute_OnEndDetection(m_CombatSolution.GetObject());
	}
	m_IsDetecting = false;
}

void UDetectMelee::UpdateWeapon()
{
	m_MeleeWeapons.Empty();

	TArray<UObject*> weapons;
	UMeleeUtils::GetImplementFromActor(GetOwner(), UMeleeWeapon::StaticClass(), weapons, false);
	for (auto _obj : weapons)
	{
		TScriptInterface<IMeleeWeapon> _weapon;
		_weapon.SetObject(_obj);
		_weapon.SetInterface(Cast<IMeleeWeapon>(_obj));;
		m_MeleeWeapons.Add(_weapon);
	}
}

void UDetectMelee::ExecuteHit(FHitResult hit)
{
	AActor *actor = hit.GetActor();
	if (m_HitActorTemps.Contains(actor))
	{
		return;
	}
	m_HitActorTemps.Add(actor);

	ECombatHitResult _hitResult = ECombatHitResult::NO_HIT;
	if (m_CombatSolution != nullptr)
	{
		ICombatSolution::Execute_OnHit(m_CombatSolution.GetObject(), actor, _hitResult);
	}

	if (m_EffectComponent != nullptr)
	{
		m_EffectComponent->OnCombatHitEffect(hit, _hitResult);
	}
}
