/*
    Author: baihan 
    class purpose: execute unit 
*/

#pragma once

#include "Action.generated.h"

UINTERFACE()
class MINDCORE_API UAction : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IAction
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
    void PrepareAction();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
    void RunningAction();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
    void FinishAction();
};