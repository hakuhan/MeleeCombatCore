/*
    Author: baihan 
    class purpose: Create will for AI 
*/

#pragma once

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
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    void DoWish();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    void CreateWish(UThing* outWishes);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    void UpdateWish();
};