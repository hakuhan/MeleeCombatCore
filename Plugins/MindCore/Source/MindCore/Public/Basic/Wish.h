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

USTRUCT(BlueprintType)
struct MINDCORE_API FWishInfo
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FThing> Wishes;
};

USTRUCT(BlueprintType)
struct FWishData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MindCore)
    TArray<FThing> OwnedThings;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MindCore)
    TArray<FThing> SeekingWishes;
};

UCLASS(Blueprintable)
class MINDCORE_API UWish : public UObject, public IWishInterface
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FWishInfo m_Info;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FWishData m_Data;

    UFUNCTION(BlueprintCallable)
    void Init(const FWishInfo& Info);
    virtual bool CreateWish_Implementation(const FThing& wish) override;
    virtual void UpdateWish_Implementation() override;
    virtual bool LoseWish_Implementation(const FString& wishName) override;
    virtual bool ObtainThing_Implementation(const FThing& thing) override;
    virtual bool LoseThing_Implementation(const FString& thingName) override;
    virtual void Reset_Implementation() override;
};