/*
    Author: baihan 
    class purpose: Input notice for melee
*/

#pragma once

#include "MeleeInputInterface.generated.h"

UINTERFACE(Blueprintable)
class MELEECORE_API UMeleeInputInterface : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API IMeleeInputInterface
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void UpdateInputState(bool canInput);
};