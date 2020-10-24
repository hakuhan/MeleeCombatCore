/*
    Author: baihan 
    class purpose: Melee Combo notice interface 
*/

#pragma once

#include "MeleeComboInterface.generated.h"

UINTERFACE()
class MELEECORE_API UMeleeComboInterface : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API IMeleeComboInterface
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnComboOver();
};