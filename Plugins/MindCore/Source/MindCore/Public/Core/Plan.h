/*
    Author: baihan 
    class purpose: Creating plan to seek wishes 
*/

#pragma once

#include "Structure/Connection.h"
#include "Structure/WishThing.h"
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

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Plan")
    void CreatePlan(const FWishThing& wish, FConnection& outPlan);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Plan")
    void UpdatePlan(FConnection& plan);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Plan")
    void RebuildPlan(int connectionID);
};