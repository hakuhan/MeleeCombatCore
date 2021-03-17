#include "Basic/BasicMind.h"

void UBasicMind::BeginPlay()
{
    Super::BeginPlay();

    if (IsMemberValid(m_remember))
    {
        m_remember->UpdateRemember();
    }
}

void UBasicMind::BeginDestroy()
{
    Super::BeginDestroy();
}

void UBasicMind::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

#pragma region Mind

void UBasicMind::DoWish_Implementation()
{
    if (IsMemberValid(m_wish))
    {
        m_wish->UpdateWish();
    }
}

void UBasicMind::DoPlan_Implementation()
{
    if (IsMemberValid(m_plan))
    {
        m_plan->UpdatePlan();
    }
}

void UBasicMind::DoImagine_Implementation()
{
}

void UBasicMind::DoRemember_Implementation()
{
    
}

#pragma endregion