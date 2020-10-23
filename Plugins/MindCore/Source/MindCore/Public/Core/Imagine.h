/*
    Author: baihan 
    class purpose: Mind imagine can react any part of mind 
*/

#pragma once

#include "Core/Wish.h"
#include "Core/Plan.h"
#include "Core/Superintend.h"
#include "Core/Action.h"
#include "Imagine.generated.h"

UINTERFACE()
class MINDCORE_API UImagine : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IImagine
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Imagine")
    void JoinWish(const TScriptInterface<IWish>& wish);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Imagine")
    void JoinPlan(const TScriptInterface<IPlan>& plan);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Imagine")
    void JoinSuperintend(const TScriptInterface<ISuperintend>& superintend);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Imagine")
    void JoinAction(const TScriptInterface<IAction>& acton);
    
};