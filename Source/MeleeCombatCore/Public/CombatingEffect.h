/*
    Author: baihan 
    class purpose: Effect throw progress of combating 
*/

#pragma once

#include "CoreMinimal.h"
#include "CombatingEffect.generated.h"

UINTERFACE()
class MELEECOMBATCORE_API UCombatingEffect : public UInterface
{
    GENERATED_BODY()
};

class MELEECOMBATCORE_API ICombatingEffect
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void ShowCombatingEffect();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void StopCombatingEffect();
};
