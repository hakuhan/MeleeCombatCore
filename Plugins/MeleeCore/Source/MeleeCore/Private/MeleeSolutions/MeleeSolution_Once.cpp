#include "MeleeSolutions/MeleeSolution_Once.h"

UMeleeSolution_Once::~UMeleeSolution_Once()
{
    m_Actors.Empty();
}

void UMeleeSolution_Once::OnHit_Implementation(AActor *attackedActor)
{
    if (!m_Actors.Contains(attackedActor))
    {
        m_Actors.Add(attackedActor);
        NoticeHit(attackedActor);
    }
}

void UMeleeSolution_Once::InitData_Implementation()
{
}

void UMeleeSolution_Once::OnStartDetection_Implementation()
{
    m_Actors.Empty();
}

void UMeleeSolution_Once::OnEndDetection_Implementation()
{
}