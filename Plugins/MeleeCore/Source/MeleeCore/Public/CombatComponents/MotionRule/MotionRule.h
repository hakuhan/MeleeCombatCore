/*
    Author: baihan 
    Date: "2021-02-01" 
    Class discription: Ruler of motion
*/

#pragma once

#include "CoreMinimal.h"
#include "MotionRule.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FMotionRuleDelegate);

USTRUCT(BlueprintType)
struct FMotionRuleEvent
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MotionRuleEvent)
    FMotionRuleDelegate Callback;
};

UENUM(BlueprintType)
enum class EMotionRuleTraverse : uint8
{
    NONE = 0 UMETA(Hidden),
    TOP_FIRST UMETA(DisplayName="Top first"),
    DOWN_FIRST UMETA(DisplayName="Down first"),
};

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
    bool IsSwitchable(int id);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool SwitchMotion(int id);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void AddCheckEvent(int id, const FMotionRuleDelegate& event);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void RemoveCheckEvent(int id);

};
