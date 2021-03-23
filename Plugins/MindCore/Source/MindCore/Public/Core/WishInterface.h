/*
    Author: baihan 
    class purpose: Create target for AI 
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
    // Be called by mind every loop
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    void DoWish();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    void CreateWish(UThing* wish);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    void UpdateWish(const FString& originName, UThing* newWish);
};