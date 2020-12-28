/*
    Author: baihan 
    class purpose: Melee Combo notice interface 
*/

#pragma once

#include "ComboInterface.generated.h"

UINTERFACE()
class MELEECORE_API UComboInterface : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API IComboInterface
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnComboOver();
};