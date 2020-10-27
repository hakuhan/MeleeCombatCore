/*
    Author: baihan 
    class purpose: Superintend data
*/

#pragma once

#include "CoreMinimal.h"
#include "Structure/Thing.h"
#include "Structure/ActionBasis.h"
#include "Way.generated.h"

USTRUCT(BlueprintType)
struct FWay : public FThing
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Way")
    FString Connection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Way")
    TArray<FActionBasis> usingActions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Way")
    int currentIndex;
};