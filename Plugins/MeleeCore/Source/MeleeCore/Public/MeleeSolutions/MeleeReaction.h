/*
    Author: baihan 
    class purpose: Melee Reaction API 
*/
#pragma once

#include "CoreMinimal.h"
#include "MeleeReaction.generated.h"

UINTERFACE(Blueprintable)
class MELEECORE_API UMeleeReaction : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API IMeleeReaction
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent)
    void OnMeleeHitted(float hurts);
};