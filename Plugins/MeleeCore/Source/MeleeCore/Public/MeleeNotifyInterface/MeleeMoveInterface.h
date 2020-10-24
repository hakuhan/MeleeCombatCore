#pragma once

#include "MeleeMoveInterface.generated.h"

UINTERFACE(Blueprintable)
class MELEECORE_API UMeleeMoveInterface : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API IMeleeMoveInterface
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void UpdateMoveState(bool canMove);
};