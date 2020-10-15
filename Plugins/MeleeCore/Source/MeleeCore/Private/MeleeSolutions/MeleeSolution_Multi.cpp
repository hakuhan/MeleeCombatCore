#include "MeleeSolutions/MeleeSolution_Multi.h"

UMeleeSolution_Multi::~UMeleeSolution_Multi()
{
    m_Actors.Empty();
    m_IntervalTimers.Empty();
}

void UMeleeSolution_Multi::InitData_Implementation()
{
    auto info = (FHurtMulti *)&m_HurtInfo;
    if (info)
    {
        m_MeleeInterval = info->interval;
    }
}

void UMeleeSolution_Multi::OnStartDetection_Implementation()
{
    m_Actors.Empty();
    m_IntervalTimers.Empty();
}

void UMeleeSolution_Multi::OnHit_Implementation(AActor *actor)
{
    if (!IsCooling(actor))
    {
        m_Actors.Add(actor);
        NoticeHit(actor);

        GetWorld()->GetTimerManager().SetTimer(m_IntervalTimers[actor], this, &UMeleeSolution_Multi::CoolOver, m_MeleeInterval, false);
    }
}

void UMeleeSolution_Multi::OnEndDetection_Implementation()
{
}

bool UMeleeSolution_Multi::IsCooling(AActor *hittedActor)
{
    bool result = false;

    if (!m_IntervalTimers.Contains(hittedActor))
    {
        result = false;
        FTimerHandle timer;
        m_IntervalTimers.Add(hittedActor, timer);
    }
    else
    {
        result = GetWorld()->GetTimerManager().IsTimerActive(m_IntervalTimers[hittedActor]);
    }

    return result;
}

void UMeleeSolution_Multi::CoolOver()
{
}