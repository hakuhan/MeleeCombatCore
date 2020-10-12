// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyStates/AttackTypeNotifyState.h"

void UAttackTypeNotifyState::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
    m_combat = Cast<UCombatComponent>(MeshComp->GetOwner()->GetComponentByClass(UCombatComponent::StaticClass()));

    if (m_combat)
    {
        m_combat->UpdateHurts(m_hurtType);
    }
}

void UAttackTypeNotifyState::NotifyTick(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float FrameDeltaTime)
{
}

void UAttackTypeNotifyState::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    if (m_combat)
    {
        m_combat->ResetHurts();
    }
}

void UAttackTypeNotifyState::BeginDestroy()
{
    m_combat = nullptr;
}