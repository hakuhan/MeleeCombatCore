/*
    Author: baihan 
    class purpose: Create target for AI 
*/

#pragma once

#include "Structure/Thing.h"
#include "WishInterface.generated.h"

UINTERFACE(Blueprintable)
class MINDCORE_API UWishInterface : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IWishInterface
{
    GENERATED_BODY()

public:
    // Be called by mind every loop
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    bool CreateWish(const FThing& wish);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    void UpdateWish();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    bool LoseWish(const FString& wishName);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    bool ObtainThing(const FThing& thing);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    bool LoseThing(const FString& thingName);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    void Reset();
};