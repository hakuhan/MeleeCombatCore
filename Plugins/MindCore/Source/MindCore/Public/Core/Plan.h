/*
    Author: baihan 
    class purpose: Creating plan to seek wishes 
*/

#pragma once

#include "Core/Imagine.h"
#include "Core/Remember.h"
#include "plan.generated.h"

UINTERFACE()
class MINDCORE_API UPlan : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IPlan
{
    GENERATED_BODY()

    friend class IImagine;
    friend class IRemember;

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Plan")
    void CreatePlan(const UThing* wish);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Plan")
    void UpdatePlan();
};