/*
    Author: baihan 
    class purpose: Create for mark thing 
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Structure/Thing.h"

#include "ThingComponent.generated.h"

UCLASS(ClassGroup = (MindCore), meta = (BlueprintSpawnableComponent))
class MINDCORE_API UThingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thing")
    FThing thing;

    UThingComponent();

    // TODO Check thing
    // void CheckThing();
};