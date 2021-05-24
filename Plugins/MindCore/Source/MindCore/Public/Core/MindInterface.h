/*
    Author: baihan 
    class purpose: Main Mind interface 
*/

#pragma once
#include "MindInterface.generated.h"

UINTERFACE(Blueprintable)
class MINDCORE_API UMindInterface : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IMindInterface
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void DoWish();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void DoBehavior();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void DoImagine();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void GetRemember(TScriptInterface<IRememberInterface>& outRemember);
};