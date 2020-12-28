#pragma once

#include "CombatMoveInterface.generated.h"

UINTERFACE(Blueprintable)
class MELEECORE_API UCombatMoveInterface : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API ICombatMoveInterface
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void UpdateMoveState(bool canMove);
};