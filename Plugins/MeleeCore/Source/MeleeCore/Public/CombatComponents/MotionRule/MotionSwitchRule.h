/*
    Author: baihan 
    Date: "2021-02-01" 
    Class discription: Ruler of motion
*/

#pragma once

#include "CoreMinimal.h"
#include "MotionSwitchRule.generated.h"

UINTERFACE()
class MELEECORE_API UMotionSwitchRule : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API IMotionSwitchRule
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool IsSwitchable(int id);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SwitchMotion(int id);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void EndMotion(int id);
};
