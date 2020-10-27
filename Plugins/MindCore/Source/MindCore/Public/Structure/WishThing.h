#pragma once

#include "Structure/Thing.h"
#include "WishThing.generated.h"

USTRUCT(BlueprintType)
struct MINDCORE_API FWishThing : public FThing
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WishThing")
    TArray<FString> Wishing;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WishThing")
    TArray<FString> owned;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WishThing")
    TArray<FString> seeking;
};