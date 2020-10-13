// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyStates/CombatEffectAnimState.h"

void UCombatEffectAnimState::BeginDestroy()
{
	Super::BeginDestroy();

	m_effect = nullptr;
}

void UCombatEffectAnimState::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
	if (!MeshComp || !MeshComp->GetOwner())
	{
		return;
	}

	m_effect = Cast<UCombatEffectComponent>(MeshComp->GetOwner()->GetComponentByClass(UCombatEffectComponent::StaticClass()));

	if (m_effect != nullptr)
	{
		m_effect->ShowCombatingEffect();
	}
}

void UCombatEffectAnimState::NotifyTick(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float FrameDeltaTime)
{
	if (m_effect != nullptr)
	{
	}
}

void UCombatEffectAnimState::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
	if (m_effect != nullptr)
	{
		m_effect->StopCombatingEffect();
	}
}
