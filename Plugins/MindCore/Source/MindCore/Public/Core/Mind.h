/*
    Author: baihan 
    class purpose: Main Mind interface 
*/

#pragma once
#include "Mind.generated.h"

UINTERFACE(Blueprintable)
class MINDCORE_API UMind : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IMind
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void DoWish();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void DoPlan();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void DoSuperintend();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void DoAction();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void DoImagine();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void DoRemember();
};