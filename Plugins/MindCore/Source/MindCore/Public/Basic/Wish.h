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

USTRUCT(BlueprintType)
struct FWishData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MindCore)
    TArray<UThing*> OwnedThings;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MindCore)
    TArray<UThing*> SeekingWishes;
};

UCLASS(Blueprintable)
class MINDCORE_API UWish : public UObject, public IWishInterface
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UWishInfo* m_Info;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FWishData m_Data;

    UFUNCTION(BlueprintCallable)
    void Init(UWishInfo* Info);
    virtual bool CreateWish_Implementation(UThing* wish) override;
    virtual void UpdateWish_Implementation() override;
    virtual bool LoseWish_Implementation(const FString& wishName) override;
    virtual bool ObtainThing_Implementation(UThing* thing) override;
    virtual bool LoseThing_Implementation(const FString& thingName) override;
    virtual void Reset_Implementation() override;
};