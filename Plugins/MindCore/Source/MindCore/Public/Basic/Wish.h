/*
    Author: baihan 
    Date: "2021-03-21" 
    Class discription: Base class creating goal for AI 
*/

#pragma once

#include "CoreMinimal.h"

#include "Core/WishInterface.h"
#include "Wish.generated.h"

UCLASS(Blueprintable)
class MINDCORE_API UWish : public UObject, public IWishInterface
{
    GENERATED_BODY()
public:
    virtual void DoWish_implementaion();
    virtual void CreateWish_Implementation(UThing* outWishes);
    virtual void UpdateWish_implementaion();
};

