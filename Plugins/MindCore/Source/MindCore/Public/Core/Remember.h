/*
    Author: baihan 
    class purpose: Remember if Mind 
*/

#pragma once

#include "CoreMinimal.h"

#include "Structure/MemoryFragment.h"
#include "Remember.generated.h"

UINTERFACE()
class MINDCORE_API URemember : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IRemember
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void UpdateRemember();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void CreateMemory(UMemoryFragment *outMemory);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void Remember(const FString& memoryID, UMemoryFragment *outfragment);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    bool Forget(const FString &memoryID);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    bool Save(const UMemoryFragment *memory);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    bool Share(const FString &memoryID, const TScriptInterface<IRemember> &target);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void Accept(const FString &memoryID, const UMemoryFragment *inMemory);

};