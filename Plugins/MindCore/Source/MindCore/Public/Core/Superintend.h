/*
    Author: baihan 
    class purpose: Create action and Superingtend all progresses 
*/

#pragma once

#include "Structure/Way.h"
#include "Structure/ActionBasis.h"
#include "Structure/Connection.h"
#include "Structure/WishThing.h"
#include "Core/Action.h"
#include "Core/Imagine.h"
#include "Core/Remember.h"
#include "Superintend.generated.h"

UINTERFACE()
class MINDCORE_API USuperintend : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API ISuperintend
{
    GENERATED_BODY()

    friend class IImagine;
    friend class IRemember;

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Superintend")
    void CreateActions(const UConnection* plan, UWay* outWay);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Superintend")
    void UpdateAction(const UConnection* plan, UWay* outWay);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Superintend")
    void UpdatePlanState(UConnection* plan);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Superintend")
    void UpdateWishState(UWishThing* wish);
};