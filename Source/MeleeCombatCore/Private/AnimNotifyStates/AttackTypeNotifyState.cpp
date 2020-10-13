// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyStates/AttackTypeNotifyState.h"

void UAttackTypeNotifyState::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
    if (!MeshComp || !MeshComp->GetOwner())
    {
        return;
    }
    m_TotalDuration = TotalDuration;
    m_TimeBuffer = 0;

    m_Combat = Cast<UCombatComponent>(MeshComp->GetOwner()->GetComponentByClass(UCombatComponent::StaticClass()));

    if (m_Combat)
    {
        m_Combat->UpdateHurts(m_Hurt, m_Solution);
        m_Combat->UpdateHurtRate(m_HurtCurve->GetFloatValue(0));
    }
}

void UAttackTypeNotifyState::NotifyTick(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float FrameDeltaTime)
{
    if (m_Combat && m_HurtCurve)
    {
        m_TimeBuffer += FrameDeltaTime;
        float currentRate = m_HurtCurve->GetFloatValue(m_TimeBuffer / m_TotalDuration);
        m_Combat->UpdateHurtRate(currentRate);
    }
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
    Super::BeginDestroy();

    m_Combat = nullptr;
}