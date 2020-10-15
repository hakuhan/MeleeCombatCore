// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyStates/AnimNotifyState_MeleeCombat.h"

void UAnimNotifyState_MeleeCombat::BeginDestroy()
{
    Super::BeginDestroy();

    m_MeleeCombat = nullptr;
    m_HurtCurve = nullptr;
}

void UAnimNotifyState_MeleeCombat::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
    if (!MeshComp || !MeshComp->GetOwner())
    {
        return;
    }

    m_TotalDuration = TotalDuration;
    m_TimeBuffer = 0;

    m_MeleeCombat = Cast<UMeleeCombat>(MeshComp->GetOwner()->GetComponentByClass(UMeleeCombat::StaticClass()));

    if (m_MeleeCombat)
    {
        m_MeleeCombat->StartDetection();
        m_MeleeCombat->UpdateHurts(m_Hurt, m_Solution);
        m_MeleeCombat->UpdateHurtRate(m_HurtCurve->GetFloatValue(0));
    }
}

void UAnimNotifyState_MeleeCombat::NotifyTick(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float FrameDeltaTime)
{
    if (m_MeleeCombat && m_HurtCurve)
    {
        m_TimeBuffer += FrameDeltaTime;
        float currentRate = m_HurtCurve->GetFloatValue(m_TimeBuffer / m_TotalDuration);
        m_MeleeCombat->UpdateHurtRate(currentRate);
    }
}

void UAnimNotifyState_MeleeCombat::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    if (m_MeleeCombat)
    {
        m_MeleeCombat->EndDetection();
        m_MeleeCombat->ResetHurts();
    }
}