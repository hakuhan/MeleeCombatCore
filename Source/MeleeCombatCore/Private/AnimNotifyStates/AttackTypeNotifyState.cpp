// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyStates/AttackTypeNotifyState.h"

void UAttackTypeNotifyState::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
    m_Combat = Cast<UCombatComponent>(MeshComp->GetOwner()->GetComponentByClass(UCombatComponent::StaticClass()));

    if (m_Combat)
    {
        m_Combat->UpdateHurts(m_Hurt, m_Solution);
    }
}

void UAttackTypeNotifyState::NotifyTick(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float FrameDeltaTime)
{
}

void UAttackTypeNotifyState::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    if (m_Combat)
    {
        m_Combat->ResetHurts();
    }
}

void UAttackTypeNotifyState::BeginDestroy()
{
    m_Combat = nullptr;
}