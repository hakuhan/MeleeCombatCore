/*
    Author: baihan 
    class purpose: Mark for every thing that can be recognized by Mind
*/
#pragma once

#include "CoreMinimal.h"
#include "Thing.generated.h"

USTRUCT(BlueprintType)
struct MINDCORE_API FThing
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    FString thingType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    FString name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    FString Description;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    bool Disappear;
};