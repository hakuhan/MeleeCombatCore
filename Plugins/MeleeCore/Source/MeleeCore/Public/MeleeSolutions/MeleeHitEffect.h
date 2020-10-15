/*
    Author: baihan 
    class purpose: Hit effect interface 
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "MeleeCoreStructures/MeleeStructure.h"
#include "MeleeHitEffect.generated.h"

UINTERFACE(Blueprintable)
class MELEECORE_API UMeleeHitEffect : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API IMeleeHitEffect
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnMeleeFirstHitEffect(FHitResult hitInfo, ECombatHitResult hitType);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnMeleeHitEffect(FHitResult hitInfo, ECombatHitResult hitType);
};
