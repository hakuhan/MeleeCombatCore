/*
    Author: baihan 
    class purpose: Create will for AI 
*/

#pragma once

#include "Wish.generated.h"

UINTERFACE(Blueprintable)
class MINDCORE_API UWish : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IWish
{
    GENERATED_BODY()
public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    void CreateWish();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    void UpdateWish();
};