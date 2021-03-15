/*
    Author: baihan 
    class purpose: Mind imagine can react any part of mind 
*/

#pragma once

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
    void Imaging();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Imagine")
    void JoinWish(TScriptInterface<IWish>& wish);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Imagine")
    void JoinPlan(TScriptInterface<IPlan>& plan);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Imagine")
    void JoinAction(TScriptInterface<IAction>& acton);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Imagine")
    void JoinMemory(TScriptInterface<IAction>& acton);
};