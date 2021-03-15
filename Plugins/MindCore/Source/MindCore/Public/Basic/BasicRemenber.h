/*
    Author: baihan 
    class purpose: Basic remenber 
*/

#pragma once

#include "CoreMinimal.h"
#include "Core/Remember.h"

#include "Structure/MemoryFragment.h"

#include "BasicRemenber.generated.h"

UCLASS(Blueprintable)
class MINDCORE_API UBasicRemenber : public UObject, public IRemember
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    TArray<UMemoryFragment*> m_Memories;
    int m_CurrentIndex;

public:
    UBasicRemenber();
    ~UBasicRemenber();

    virtual void UpdateRemember_Implementation();

    virtual void CreateMemory_Implementation(UMemoryFragment *outMemory) override;

    virtual void Remember_Implementation(const FString& memoryID, UMemoryFragment *outfragment) override;

    virtual bool Forget_Implementation(const FString &memoryID) override;

    virtual bool Save_Implementation(const UMemoryFragment *memory) override;

    virtual bool Share_Implementation(const FString &memoryID, const TScriptInterface<IRemember> &target) override;

    virtual void Accept_Implementation(const FString &memoryID, const UMemoryFragment *inMemory) override;

    void Clean();
};
