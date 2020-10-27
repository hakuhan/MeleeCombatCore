/*
    Author: baihan 
    class purpose: Remember if Mind 
*/

#pragma once

#include "Structure/Memory.h"
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
    void GetAllWishes(TArray<FWishThing>& outWishes);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void CurrentMemory(FMemoryFragment &outMemory);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void CreateMemory(FMemoryFragment &outMemory);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    bool Conatins(FString memoryID);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void GetMemory(FString memoryID, FMemoryFragment &outMemory);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void Store(const FMemoryFragment &fragment);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    bool Share(FString memoryID, const TScriptInterface<IRemember> &target);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void Accept(FString memoryID, FMemoryFragment &inMemory);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    bool RemoveMemory(FString memoryID);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void Clean();
};