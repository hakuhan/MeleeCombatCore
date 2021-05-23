/*
    Author: baihan 
    class purpose: Mind imagine can react any part of mind 
*/

#pragma once
#include "Core/BehaviorInterface.h"
#include "Core/WishInterface.h"
#include "Core/ActionInterface.h"
#include "Core/RememberInterface.h"
#include "ImagineInterface.generated.h"

UINTERFACE()
class MINDCORE_API UImagineInterface : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IImagineInterface
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Imagine")
    void Imaging();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Imagine")
    void JoinWish(TScriptInterface<IWishInterface>& wish);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Imagine")
    void JoinBehavior(TScriptInterface<IBehaviorInterface>& plan);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Imagine")
    void JoinAction(TScriptInterface<IActionInterface>& acton);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Imagine")
    void JoinMemory(TScriptInterface<IRememberInterface>& remember);
};