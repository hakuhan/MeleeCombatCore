#pragma once

#include "Structure/Thing.h"
#include "WishThing.generated.h"

UCLASS(Blueprintable)
class MINDCORE_API UWishThing : public UThing
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WishThing")
    TArray<FString> Wishing;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WishThing")
    TArray<FString> owned;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WishThing")
    TArray<FString> seeking;
};