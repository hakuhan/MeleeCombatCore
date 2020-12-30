/*
    Author: baihan 
    class purpose: Hit effect interface 
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "MeleeCoreStructures/MeleeStructure.h"
#include "CombatHitEffect.generated.h"

UINTERFACE(Blueprintable)
class MELEECORE_API UCombatHitEffect : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API ICombatHitEffect
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnMeleeFirstHitEffect(FHitResult hitInfo, ECombatHitResult hitType);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnCombatHitEffect(FHitResult hitInfo, ECombatHitResult hitType);
};
