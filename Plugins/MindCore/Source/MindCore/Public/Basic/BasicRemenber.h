/*
    Author: baihan 
    class purpose: Basic remenber 
*/

#pragma once

#include "CoreMinimal.h"
#include "Core/Remember.h"

#include "Structure/Memory.h"

#include "BasicRemenber.generated.h"

UCLASS(Blueprintable)
class MINDCORE_API UBasicRemenber : public UObject, public IRemember
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    UMindMemory* m_Memory;
    int m_CurrentIndex;

public:
    UBasicRemenber();
    ~UBasicRemenber();

#pragma region Implement Rember
    virtual void GetAllWishes_Implementation(TArray<UWishThing *> &outWishes) override;

    virtual void CurrentMemory_Implementation(UMemoryFragment *outFragment) override;

    virtual bool Contains_Implementation(const FString &memoryID);

    virtual void CreateMemory_Implementation(UMemoryFragment *outMemory) override;

    virtual void GetMemory_Implementation(const FString &memoryID, UMemoryFragment *outMemory) override;

    virtual void LoadMemory_Implementation();

    virtual void Store_Implementation(const UMemoryFragment *fragment) override;

    virtual bool Share_Implementation(const FString &memoryID, const TScriptInterface<IRemember> &target) override;

    virtual void Accept_Implementation(const FString &memoryID, const UMemoryFragment *inMemory) override;

    virtual bool RemoveMemory_Implementation(const FString &memoryID) override;

    virtual void Clean_Implementation() override;

#pragma endregion

    /** Get first memery that is unfinished except all memory finished*/
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BasicRemember")
    int GetFirstMemory(UMemoryFragment *outMemory, bool createNew = true);

    /** Sort memory default by fish state that means unfinished first*/
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BasicRemember")
    void SortMemory();
};
