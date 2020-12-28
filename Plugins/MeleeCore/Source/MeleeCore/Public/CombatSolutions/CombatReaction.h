/*
    Author: baihan 
    class purpose: Melee Reaction API 
*/
#pragma once

#include "CoreMinimal.h"
#include "CombatReaction.generated.h"

UINTERFACE(Blueprintable)
class MELEECORE_API UCombatReaction : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API ICombatReaction
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent)
    void OnMeleeHitted(float hurts);
    // void OnMeleeHitted(float hurts, UPARAM(ref) ECombatHitResult &outResult);
    // ECombatHitResult OnMeleeHitted(float hurts);

    UFUNCTION(BlueprintNativeEvent)
    ECombatHitResult HitResult();

};