/*
    Author: baihan 
    class purpose: Mind memory data 
*/

#pragma once

#include "CoreMinimal.h"

#include "Structure/Thing.h"
#include "Structure/WishThing.h"
#include "Structure/Connection.h"
#include "Structure/Way.h"

#include "Memory.generated.h"

USTRUCT(BlueprintType)
struct MINDCORE_API FMemoryFragment
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory")
    FWishThing wishData;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory")
    FConnection planData;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory")
    FWay surperintendData;
};

USTRUCT(BlueprintType)
struct MINDCORE_API FMindMemory : public FThing
{
    GENERATED_USTRUCT_BODY()

public:
    TArray<FMemoryFragment> fragment;
};
