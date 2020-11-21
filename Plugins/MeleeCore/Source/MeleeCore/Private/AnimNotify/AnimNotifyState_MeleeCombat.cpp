#include "AnimNotify/AnimNotifyState_MeleeCombat.h"

UAnimNotifyState_MeleeCombat::UAnimNotifyState_MeleeCombat()
{
    auto curveObj = ConstructorHelpers::FObjectFinder<UCurveFloat>(TEXT("/MeleeCore/Curves/C_DefaultCombat.C_DefaultCombat"));
    if (curveObj.Object != nullptr)
    {
        m_HurtCurve = curveObj.Object;
    }
}

void UAnimNotifyState_MeleeCombat::BeginDestroy()
{
    Super::BeginDestroy();

    m_MeleeCombat = nullptr;
    m_HurtCurve = nullptr;
}

void UAnimNotifyState_MeleeCombat::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
    {
        return;
    }

    m_TotalDuration = TotalDuration;
    m_TimeBuffer = 0;

    m_MeleeCombat = Cast<UMeleeCombat>(MeshComp->GetOwner()->GetComponentByClass(UMeleeCombat::StaticClass()));

    if (m_MeleeCombat != nullptr && m_HurtCurve != nullptr)
    {
        m_MeleeCombat->StartDetection();
        m_MeleeCombat->UpdateHurts(m_Hurt, m_Solution);
        m_MeleeCombat->UpdateHurtRate(m_HurtCurve->GetFloatValue(0));
        m_MeleeCombat->UpdateWeaponMask(m_WeaponFlags);
    }
}

void UAnimNotifyState_MeleeCombat::NotifyTick(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float FrameDeltaTime)
{
    if (m_MeleeCombat != nullptr && m_HurtCurve != nullptr)
    {
        m_TimeBuffer += FrameDeltaTime;
        float currentRate = m_HurtCurve->GetFloatValue(m_TimeBuffer / m_TotalDuration);
        m_MeleeCombat->UpdateHurtRate(currentRate);
    }
}

void UAnimNotifyState_MeleeCombat::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    if (m_MeleeCombat != nullptr)
    {
        m_MeleeCombat->EndDetection();
        m_MeleeCombat->ResetHurts();
    }
}