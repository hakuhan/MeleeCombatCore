/*
    Author: baihan 
    class purpose: Basic remenber 
*/

#pragma once

#include "CoreMinimal.h"
#include "Core/Remember.h"

#include "Structure/Memory.h"

#include "BasicRemenber.generated.h"

UCLASS()
class MINDCORE_API UBasicRemenber : public UObject, public IRemember
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FMindMemory m_Memory;
    int m_CurrentIndex;
    UBasicRemenber();
    ~UBasicRemenber();

#pragma region Implement Rember
    virtual void GetAllWishes_Implementation(TArray<FWishThing>& outWishes) override;

    virtual void CurrentMemory_Implementation(FMemoryFragment &outFragment) override;

    virtual bool Contains_Implementation(const FString& memoryID);

    virtual void CreateMemory_Implementation(FMemoryFragment &outMemory) override;

    virtual void GetMemory_Implementation(const FString& memoryID, FMemoryFragment &outMemory) override;

    virtual void Store_Implementation(const FMemoryFragment &fragment) override;

    virtual bool Share_Implementation(const FString& memoryID, const TScriptInterface<IRemember> &target) override;

    virtual void Accept_Implementation(const FString& memoryID, FMemoryFragment &inMemory) override;

    virtual bool RemoveMemory_Implementation(const FString& memoryID) override;

    virtual void Clean_Implementation() override;

#pragma endregion

    /** Get first memery that is unfinished except all memory finished*/
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BasicRemember")
    int GetFirstMemory(FMemoryFragment& outMemory, bool createNew = true);
    
    /** Sort memory default by fish state that means unfinished first*/
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BasicRemember")
    void SortMemory();
};
