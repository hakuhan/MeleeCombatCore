// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatComponent.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	m_isDetecting = false;
	m_isShowTrace = false;
	m_channel = ECollisionChannel::ECC_GameTraceChannel1;
}

// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	UpdateWeapon();

	// init deal data
	auto dealInfo = m_hitSolutionInfo.GetRow<FCombatSolution>("Find attack deal");
	if (dealInfo)
	{
		auto dealObj = NewObject<UObject>(this, dealInfo->solutionClass);
		auto solutionInfo = dealInfo->solutionInfo.GetRow<FHitSolutionInfo>("Get Deal attak data");
		if (dealObj && solutionInfo)
		{
			m_solution = Cast<IHitSolution>(dealObj);
			m_solution->Init(*solutionInfo);
		}
	}
}

// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_isDetecting)
	{
		// attack check
		for (int i = 0; i < m_weapons.Num(); ++i)
		{
			for (int j = 0; j < m_weapons[i].socketNames.Num(); ++j)
			{
				// 1. Check every single socket
				auto debugTrace = EDrawDebugTrace::ForDuration;
				if (!m_isShowTrace)
				{
					debugTrace = EDrawDebugTrace::None;
				}
				auto traceColor = FLinearColor::Green;
				auto collisionColor = FLinearColor::Red;
				auto channel = UEngineTypes::ConvertToTraceType(m_channel);

				// check slot location cache
				auto socketName = m_weapons[i].socketNames[j];
				FVector crtLocation = m_weapons[i].weapon->GetSocketLocation(socketName);
				if (m_weapons[i].tempSocketLocation.Num() <= j)
				{
					m_weapons[i].tempSocketLocation.Add(crtLocation);
				}
				FVector preLocation = m_weapons[i].tempSocketLocation[j];

				auto world = GetOwner()->GetWorld();
				TArray<FHitResult> hits;
				TArray<AActor *> arrayIgnoreActor;
				UKismetSystemLibrary::LineTraceMulti(world, preLocation, crtLocation, channel, true, arrayIgnoreActor, debugTrace, hits, true, traceColor, collisionColor);
				for (auto hit : hits)
				{
					if (m_solution)
					{
						// UE_LOG(LogTemp, Warning, TEXT("Attack player"));
						IHitSolution::Execute_OnHit(Cast<UObject>(m_solution), hit.GetActor());
					}
					// UE_LOG(LogTemp, Warning, TEXT("Attack player: %s"), *hit.GetActor()->GetFName().ToString());
				}

				// 2. Check trace between sokets
				int k = j + 1;
				if (k < m_weapons[i].socketNames.Num())
				{
					auto nextSocket = m_weapons[i].socketNames[k];
					auto nextSocketLocation = m_weapons[i].weapon->GetSocketLocation(nextSocket);
					TArray<FHitResult> hitsBySockets;
					UKismetSystemLibrary::LineTraceMulti(world, crtLocation, nextSocketLocation, channel, true, arrayIgnoreActor, debugTrace, hitsBySockets, true, traceColor, collisionColor);

					for (auto h : hitsBySockets)
					{
						if (m_solution)
						{
							IHitSolution::Execute_OnHit(Cast<UObject>(m_solution), h.GetActor());
						}
						// UE_LOG(LogTemp, Warning, TEXT("Sockets attack player: %s"), *h.GetActor()->GetFName().ToString());
					}
				}

				m_weapons[i].tempSocketLocation[j] = crtLocation;
			}
		}
	}
}

void UCombatComponent::StartDetection()
{
	if (m_solution)
	{
		IHitSolution::Execute_OnStartDetection(Cast<UObject>(Cast<UObject>(m_solution)));
	}
	m_isDetecting = true;

	ResetData();
}

void UCombatComponent::ResetData()
{
	for (int i = 0; i < m_weapons.Num(); ++i)
	{
		m_weapons[i].tempSocketLocation.Empty();
	}
}

void UCombatComponent::EndDetection()
{
	if (m_solution)
	{
		IHitSolution::Execute_OnEndDetection(Cast<UObject>(m_solution));
	}
	m_isDetecting = false;
}

void UCombatComponent::UpdateWeapon()
{
	m_weapons.Empty();

	// Add weapon info
	for (auto tag : m_weaponTargs)
	{
		auto weapons = GetOwner()->GetComponentsByTag(UMeshComponent::StaticClass(), FName(tag));
		for (auto w : weapons)
		{
			auto wData = new FCombatWeapon();
			wData->weapon = Cast<UMeshComponent>(w);
			wData->socketNames.Append(wData->weapon->GetAllSocketNames());
			m_weapons.Add(*wData);
		}
	}
}
