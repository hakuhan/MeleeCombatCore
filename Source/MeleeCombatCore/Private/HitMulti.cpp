#include "HitMulti.h"

void UHitMulti::InitData_Implementation()
{
    
}

void UHitMulti::OnStartDetection_Implementation()
{
    m_actors.Empty();
}

void UHitMulti::OnHit_Implementation(AActor *actor)
{
    m_actors.Add(actor);
    NoticeHit(actor);
}

void UHitMulti::OnEndDetection_Implementation()
{
}