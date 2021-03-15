/*
    Author: baihan 
    class purpose: execute unit 
*/

#pragma once

#include "Structure/ActionInfo.h"
#include "Core/Imagine.h"
#include "Core/Remember.h"
#include "Action.generated.h"

UINTERFACE()
class MINDCORE_API UAction : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IAction
{
    GENERATED_BODY()

    friend class IImagine;
    friend class IRemember;

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
    void PrepareAction(UActionInfo* basis);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
    void RunningAction(UActionInfo* basis);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
    void FinishAction(UActionInfo* basis);
};