/*
    Author: baihan 
    class purpose: Remember if Mind 
*/

#pragma once

#include "CoreMinimal.h"

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
    bool Contains(const FString& memoryID);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void GetMemory(const FString& memoryID, FMemoryFragment &outMemory);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void Store(const FMemoryFragment &fragment);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    bool Share(const FString& memoryID, const TScriptInterface<IRemember> &target);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void Accept(const FString& memoryID, FMemoryFragment &inMemory);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    bool RemoveMemory(const FString& memoryID);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void Clean();
};