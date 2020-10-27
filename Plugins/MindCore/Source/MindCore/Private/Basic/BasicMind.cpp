#include "Basic/BasicMind.h"

void UBasicMind::BeginPlay()
{
    Super::BeginPlay();
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
    if (m_wish != nullptr)
    {
        // IWish::Execute_CreateWish(m_wish.GetObject(), );
    }
}

void UBasicMind::DoPlan_Implementation()
{

}

void UBasicMind::DoSuperintend_Implementation()
{

}

void UBasicMind::DoAction_Implementation()
{

}

void UBasicMind::DoImagine_Implementation()
{

}

void UBasicMind::DoRemember_Implementation()
{
    FMemoryFragment fragment;
    
}

#pragma endregion