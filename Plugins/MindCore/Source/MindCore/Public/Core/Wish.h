/*
    Author: baihan 
    class purpose: Create will for AI 
*/

#pragma once

#include "Structure/WishThing.h"
#include "Wish.generated.h"

UINTERFACE(Blueprintable)
class MINDCORE_API UWish : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IWish
{
    GENERATED_BODY()

    friend class IImagine;

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    void CreateWish(TArray<FWishThing>& outWishes);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    void UpdateWish(TArray<FWishThing>& currentWishes);
};