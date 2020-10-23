/*
    Author: baihan 
    class purpose: execute unit 
*/

#pragma once

#include "Structure/ActionBasis.h"
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
    void PrepareAction(FActionBasis& basis);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
    void RunningAction(FActionBasis& basis);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
    void FinishAction(FActionBasis& basis);
};