/*
    Author: baihan 
    class purpose: receive attack event 
*/

#pragma once

#include "CoreMinimal.h"
#include "HitReaction.generated.h"

UINTERFACE(Blueprintable)
class UHitReaction : public UInterface
{
    GENERATED_BODY()
};

class MELEECOMBATCORE_API IHitReaction
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent)
    void OnHitted(float hurts);
};