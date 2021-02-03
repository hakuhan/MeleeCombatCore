/*
    Author: baihan 
    Date: "2021-02-01" 
    Class discription: Ruler of motion
*/

#pragma once

#include "CoreMinimal.h"
#include "MotionRule.generated.h"

UINTERFACE()
class MELEECORE_API UMotionRule : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API IMotionRule
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool IsRuleActive();
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetRuleActive(bool bActive);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool IsSwitchable(int level);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool SwitchMotion(int level);

};
