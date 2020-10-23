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
    void Store(FMemoryFragment& outFragment);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void Recall(int memoryID);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void Share(int memoryID);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remember")
    void Accept(int memoryID);
};