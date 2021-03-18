/*
    Author: baihan 
    class purpose: execute unit 
*/

#pragma once

#include "ActionInterface.generated.h"

UINTERFACE()
class MINDCORE_API UActionInterface : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IActionInterface
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