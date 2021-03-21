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
    if (IsMemberValid(m_Wish))
    {
        m_Wish->DoWish();
    }
}

void UMind::DoPlan_Implementation()
{
    if (IsMemberValid(m_Behavior))
    {
        m_Behavior->Behave();
    }
}

void UMind::DoImagine_Implementation()
{
    m_Imagine->Imaging();
}

#pragma endregion