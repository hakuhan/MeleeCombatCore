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