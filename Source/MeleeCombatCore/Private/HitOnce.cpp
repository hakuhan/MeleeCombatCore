#include "HitOnce.h"

UHitOnce::~UHitOnce()
{
    m_actors.Empty();
}

void UHitOnce::OnHit_Implementation(AActor *attackedActor)
{
    if (!m_actors.Contains(attackedActor))
    {
        m_actors.Add(attackedActor);
        NoticeHit(attackedActor);
    }
}

void UHitOnce::InitData_Implementation()
{
}

void UHitOnce::OnStartDetection_Implementation()
{
    m_actors.Empty();
}

void UHitOnce::OnEndDetection_Implementation()
{
}