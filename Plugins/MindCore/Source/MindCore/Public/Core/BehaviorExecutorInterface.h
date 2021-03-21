/*
    Author: baihan 
    Date: "2021-03-21" 
    Class discription: Define how to make wishes come true 
*/

#pragma once

#include "BehaviorExecutorInterface.generated.h"

UINTERFACE(Blueprintable)
class MINDCORE_API UBehaviorExecutorInterface : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IBehaviorExecutorInterface
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void CreateBehavior();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void UpdateBehavior();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void ExecuteBehavior();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void GetExecuteState();
};