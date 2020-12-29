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
	m_weaponMask = weaponMask;
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
		// attack check
		for (int i = 0; i < m_MeleeWeapons.Num(); ++i)
		{
			if (!m_MeleeWeapons[i]->IsTargetWeapon(m_weaponMask))
			{
				continue;
			}

			for (int j = 0; j < m_MeleeWeapons[i]->info.socketNames.Num(); ++j)
			{
				// 1. Check every single socket
				auto debugTrace = EDrawDebugTrace::ForDuration;
				if (!m_IsShowTrace)
				{
					debugTrace = EDrawDebugTrace::None;
				}
				auto traceColor = FLinearColor::Green;
				auto collisionColor = FLinearColor::Red;
				auto channel = UEngineTypes::ConvertToTraceType(m_Channel);

				// check slot location cache
				auto socketName = m_MeleeWeapons[i]->info.socketNames[j];
				FVector crtLocation = m_MeleeWeapons[i]->GetSocketLocation(socketName);
				if (m_MeleeWeapons[i]->info.tempSocketLocation.Num() <= j)
				{
					m_MeleeWeapons[i]->info.tempSocketLocation.Add(crtLocation);
				}
				FVector preLocation = m_MeleeWeapons[i]->info.tempSocketLocation[j];

				auto world = GetOwner()->GetWorld();
				TArray<FHitResult> hits;
				TArray<AActor *> arrayIgnoreActor;
				UKismetSystemLibrary::LineTraceMulti(world, preLocation, crtLocation, channel, true, arrayIgnoreActor, debugTrace, hits, true, traceColor, collisionColor);
				for (auto hit : hits)
				{
					ExecuteHit(hit);
				}

				// 2. Check trace between sokets
				int k = j + 1;
				if (k < m_MeleeWeapons[i]->info.socketNames.Num())
				{
					auto nextSocket = m_MeleeWeapons[i]->info.socketNames[k];
					auto nextSocketLocation = m_MeleeWeapons[i]->GetSocketLocation(nextSocket);
					TArray<FHitResult> hitsBySockets;
					UKismetSystemLibrary::LineTraceMulti(world, crtLocation, nextSocketLocation, channel, true, arrayIgnoreActor, debugTrace, hitsBySockets, true, traceColor, collisionColor);

					for (auto h : hitsBySockets)
					{
						ExecuteHit(h);
					}
				}

				m_MeleeWeapons[i]->info.tempSocketLocation[j] = crtLocation;
			}
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
		m_MeleeWeapons[i]->info.tempSocketLocation.Empty();
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

	GetOwner()->GetComponents<UMeleeWeapon>(m_MeleeWeapons);
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
