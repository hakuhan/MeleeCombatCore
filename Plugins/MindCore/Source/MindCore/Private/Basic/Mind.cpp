#include "Basic/Mind.h"

void UMind::BeginPlay()
{
    Super::BeginPlay();
}

void UMind::BeginDestroy()
{
    Super::BeginDestroy();
}

void UMind::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

#pragma region Mind

void UMind::DoWish_Implementation()
{
    if (IsMemberValid(m_wish))
    {
        m_wish->DoWish();
    }
}

void UMind::DoPlan_Implementation()
{
    if (IsMemberValid(m_plan))
    {
        m_plan->DoPlan();
    }
}

void UMind::DoImagine_Implementation()
{
}

void UMind::DoRemember_Implementation()
{
    
}

#pragma endregion