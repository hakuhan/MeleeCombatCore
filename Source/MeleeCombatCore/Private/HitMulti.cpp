#include "HitMulti.h"

UHitMulti::~UHitMulti()
{
    m_actors.Empty();
}

void UHitMulti::InitData_Implementation()
{
    auto info = (FHitMultiInfo *)&m_hitInfo;
    if (info)
    {
        m_hitInterval = info->interval;
    }
}

void UHitMulti::OnStartDetection_Implementation()
{
    m_actors.Empty();
}

void UHitMulti::OnHit_Implementation(AActor *actor)
{
    if (!IsCooling())
    {
        m_actors.Add(actor);
        NoticeHit(actor);

        GetWorld()->GetTimerManager().SetTimer(timeHandler, this, &UHitMulti::CoolOver, m_hitInterval, false);
    }
}

void UHitMulti::OnEndDetection_Implementation()
{
}

bool UHitMulti::IsCooling()
{
    return GetWorld()->GetTimerManager().IsTimerActive(timeHandler);
}

void UHitMulti::CoolOver()
{
}