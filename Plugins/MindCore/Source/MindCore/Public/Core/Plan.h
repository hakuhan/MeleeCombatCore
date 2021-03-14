/*
    Author: baihan 
    class purpose: Creating plan to seek wishes 
*/

#pragma once

#include "Structure/Connection.h"
#include "Structure/WishThing.h"
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
    void CreatePlan(const UWishThing* wish, UConnection* outPlan);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Plan")
    void UpdatePlan(UConnection* plan);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Plan")
    void RebuildPlan(int connectionID);
};