/*
    Author: baihan 
    class purpose: Creating plan to seek wishes 
*/

#pragma once

#include "Structure/Thing.h"
#include "PlanInterface.generated.h"

UINTERFACE()
class MINDCORE_API UPlanInterface : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IPlanInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Plan")
    void DoPlan();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Plan")
    void CreatePlan(const UThing* wish);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Plan")
    void UpdatePlan();
};