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
    int ConnectionID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Way")
    TArray<int> usingActionIDs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Way")
    int currentActionID;
};