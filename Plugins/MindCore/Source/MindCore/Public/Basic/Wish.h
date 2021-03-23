/*
    Author: baihan 
    Date: "2021-03-21" 
    Class discription: Base class creating goal for AI 
*/

#pragma once

#include "CoreMinimal.h"

#include "Core/WishInterface.h"
#include "Structure/Thing.h"
#include "Wish.generated.h"

UCLASS(Blueprintable)
class MINDCORE_API UWishInfo : public UThing
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<UThing*> Wishes;
};

UCLASS(Blueprintable)
class MINDCORE_API UWish : public UObject, public IWishInterface
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UWishInfo* m_Info;

    virtual void DoWish_Implementation() override;
    virtual void CreateWish_Implementation(UThing* wish) override;
    virtual void UpdateWish_Implementation(const FString& originName, UThing* newWish) override;
};

