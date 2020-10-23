#pragma once

#include "Structure/Thing.h"
#include "WishThing.generated.h"

USTRUCT(BlueprintType)
struct MINDCORE_API FWishThing : public FThing
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WishThing")
    TArray<int> Wishing;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WishThing")
    TArray<int> owned;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WishThing")
    TArray<int> seeking;
};