// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyStates/CombatAnimNotifyState.h"

void UCombatAnimNotifyState::BeginDestroy()
{
	Super::BeginDestroy();

	m_combat = nullptr;
}

void UCombatAnimNotifyState::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
	if (!MeshComp || !MeshComp->GetOwner())
	{
		return;
	}
	
	m_combat = Cast<UCombatComponent>(MeshComp->GetOwner()->GetComponentByClass(UCombatComponent::StaticClass()));

	if (m_combat != nullptr)
	{
		m_combat->StartDetection();
	}
}

void UCombatAnimNotifyState::NotifyTick(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float FrameDeltaTime)
{
	if (m_combat != nullptr)
	{
	}
}

void UCombatAnimNotifyState::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
	if (m_combat != nullptr)
	{
		m_combat->EndDetection();
	}
}
