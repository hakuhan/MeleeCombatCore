/*
    Author: baihan 
    class purpose: Create will for AI 
*/

#pragma once

#include "Structure/WishThing.h"
#include "Core/Imagine.h"
#include "Core/Remember.h"
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
    friend class IRemember;

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    void CreateWish(TArray<UWishThing*>& outWishes);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Wish")
    void UpdateWish(TArray<UWishThing*>& currentWishes);
};