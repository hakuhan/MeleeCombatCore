// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeComponents/MeleeCombat.h"

// Sets default values for this component's properties
UMeleeCombat::UMeleeCombat()
{
	PrimaryComponentTick.bCanEverTick = true;
	m_IsDetecting = false;
	m_IsShowTrace = false;
	m_Channel = ECollisionChannel::ECC_GameTraceChannel1;
}

void UMeleeCombat::BeginDestroy()
{
	Super::BeginDestroy();
	m_MeleeWeaponTargs.Empty();
	m_MeleeWeapons.Empty();
	m_HitActorTemps.Empty();
}

// Called when the game starts
void UMeleeCombat::BeginPlay()
{
	Super::BeginPlay();

	UpdateWeapon();

	// init solution data
	auto solutionInfo = m_MeleeSolutionTable.GetRow<FMeleeSolutionTable>("Find combat solution");
	if (solutionInfo)
	{
		m_DefaultSolution = solutionInfo->solutionType;

		auto dealObj = NewObject<UObject>(this, solutionInfo->solutionClass);
		auto hurtInfo = solutionInfo->hurtTable.GetRow<FHurt>("Find combat hurt");
		if (dealObj && hurtInfo)
		{
			m_MeleeSolution.SetObject(dealObj);
			m_MeleeSolution.SetInterface(Cast<IMeleeSolution>(dealObj));
			m_MeleeSolution->Init(*hurtInfo);

			// set defaul data
			m_DefaultHurt = hurtInfo->hurtType;
		}
	}

	m_EffectComponent = Cast<UMeleeEffect>(GetOwner()->GetComponentByClass(UMeleeEffect::StaticClass()));
}

void UMeleeCombat::UpdateHurts(EMeleeHurt newHurt, ECombatSolution newSolution)
{
	FMeleeSolutionTable *solutionInfo = m_MeleeSolutionTable.GetRow<FMeleeSolutionTable>("Find combat solution");
	if (newSolution != m_SolutionType)
	{
		for (auto solutionName : m_MeleeSolutionTable.DataTable->GetRowNames())
		{
			auto sRow = m_MeleeSolutionTable.DataTable->FindRow<FMeleeSolutionTable>(solutionName, "Find combat solution", true);
			if (sRow->solutionType == newSolution)
			{
				solutionInfo = sRow;
				auto solutionObj = NewObject<UObject>(this, sRow->solutionClass);
				m_MeleeSolution.SetObject(solutionObj);
				m_MeleeSolution.SetInterface(Cast<IMeleeSolution>(solutionObj));
				m_SolutionType = newSolution;
				break;
			}
		}
	}

	if (newHurt != m_HurtType)
	{
		FHurt newHurtInfo = m_MeleeSolution->m_HurtInfo;
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

		m_MeleeSolution->UpdateHurts(newHurtInfo);
	}
}

void UMeleeCombat::UpdateHurtRate(float rate)
{
	if (m_MeleeSolution)
	{
		m_MeleeSolution->UpdateHurtRate(rate);
	}
}

void UMeleeCombat::ResetHurts()
{
	UpdateHurts(m_DefaultHurt, m_DefaultSolution);
}

// Called every frame
void UMeleeCombat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	m_HitActorTemps.Empty();
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_IsDetecting)
	{
		// attack check
		for (int i = 0; i < m_MeleeWeapons.Num(); ++i)
		{
			for (int j = 0; j < m_MeleeWeapons[i].socketNames.Num(); ++j)
			{
				TArray<AActor *> tempActors;

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
				auto socketName = m_MeleeWeapons[i].socketNames[j];
				FVector crtLocation = m_MeleeWeapons[i].weapon->GetSocketLocation(socketName);
				if (m_MeleeWeapons[i].tempSocketLocation.Num() <= j)
				{
					m_MeleeWeapons[i].tempSocketLocation.Add(crtLocation);
				}
				FVector preLocation = m_MeleeWeapons[i].tempSocketLocation[j];

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
				if (k < m_MeleeWeapons[i].socketNames.Num())
				{
					auto nextSocket = m_MeleeWeapons[i].socketNames[k];
					auto nextSocketLocation = m_MeleeWeapons[i].weapon->GetSocketLocation(nextSocket);
					TArray<FHitResult> hitsBySockets;
					UKismetSystemLibrary::LineTraceMulti(world, crtLocation, nextSocketLocation, channel, true, arrayIgnoreActor, debugTrace, hitsBySockets, true, traceColor, collisionColor);

					for (auto h : hitsBySockets)
					{
						ExecuteHit(h);
					}
				}

				m_MeleeWeapons[i].tempSocketLocation[j] = crtLocation;
			}
		}
	}
}

void UMeleeCombat::StartDetection()
{
	if (m_MeleeSolution)
	{
		IMeleeSolution::Execute_OnStartDetection(m_MeleeSolution.GetObject());
	}
	m_IsDetecting = true;

	ResetData();
}

void UMeleeCombat::ResetData()
{
	for (int i = 0; i < m_MeleeWeapons.Num(); ++i)
	{
		m_MeleeWeapons[i].tempSocketLocation.Empty();
	}
	if (m_EffectComponent)
	{
		m_EffectComponent->ResetData();
	}
}

void UMeleeCombat::EndDetection()
{
	if (m_MeleeSolution)
	{
		IMeleeSolution::Execute_OnEndDetection(m_MeleeSolution.GetObject());
	}
	m_IsDetecting = false;
}

void UMeleeCombat::UpdateWeapon()
{
	m_MeleeWeapons.Empty();

	// Add weapon info
	for (auto tag : m_MeleeWeaponTargs)
	{
		auto weapons = GetOwner()->GetComponentsByTag(UMeshComponent::StaticClass(), FName(tag));
		for (auto w : weapons)
		{
			auto wData = new FMeleeWeapon();
			wData->weapon = Cast<UMeshComponent>(w);
			wData->socketNames.Append(wData->weapon->GetAllSocketNames());
			m_MeleeWeapons.Add(*wData);
		}
	}
}

void UMeleeCombat::ExecuteHit(FHitResult hit)
{
	AActor *actor = hit.GetActor();
	if (m_HitActorTemps.Contains(actor))
	{
		return;
	}
	m_HitActorTemps.Add(actor);

	ECombatHitResult _hitResult = ECombatHitResult::NO_INJURY_HIT;
	if (m_MeleeSolution)
	{
		IMeleeSolution::Execute_OnHit(m_MeleeSolution.GetObject(), actor, _hitResult);
	}

	if (m_EffectComponent)
	{
		m_EffectComponent->OnCombatHitEffect(hit, _hitResult);
	}
}

