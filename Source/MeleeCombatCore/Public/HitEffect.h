/*
    Author: baihan 
    class purpose: Hit effect interface 
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "HitEffect.generated.h"

UINTERFACE()
class MELEECOMBATCORE_API UHitEffect : public UInterface
{
    GENERATED_BODY()
};

class MELEECOMBATCORE_API IHitEffect
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void FirstHitEffect(FHitResult hitInfo);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void HitEffect(FHitResult hitInfo);
};
