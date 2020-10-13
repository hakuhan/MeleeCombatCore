#include "HitMulti.h"

UHitMulti::~UHitMulti()
{
    m_actors.Empty();
    m_intervalTimers.Empty();
}

void UHitMulti::InitData_Implementation()
{
    auto info = (FHurtMulti *)&m_HurtInfo;
    if (info)
    {
        m_hitInterval = info->interval;
    }
}

void UHitMulti::OnStartDetection_Implementation()
{
    m_actors.Empty();
    m_intervalTimers.Empty();
}

void UHitMulti::OnHit_Implementation(AActor *actor)
{
    if (!IsCooling(actor))
    {
        m_actors.Add(actor);
        NoticeHit(actor);

        GetWorld()->GetTimerManager().SetTimer(m_intervalTimers[actor], this, &UHitMulti::CoolOver, m_hitInterval, false);
    }
}

void UHitMulti::OnEndDetection_Implementation()
{
}

bool UHitMulti::IsCooling(AActor *hittedActor)
{
    bool result = false;

    if (!m_intervalTimers.Contains(hittedActor))
    {
        result = false;
        FTimerHandle timer;
        m_intervalTimers.Add(hittedActor, timer);
    }
    else
    {
        result = GetWorld()->GetTimerManager().IsTimerActive(m_intervalTimers[hittedActor]);
    }

    return result;
}

void UHitMulti::CoolOver()
{
}