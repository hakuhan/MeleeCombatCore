/*
    Author: baihan 
    Date: "2021-02-18" 
    Class discription: Provide basic motion rules 
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MotionSwitchRule.h"
#include "MotionSwitchRuleBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FMotionRuleDelegate);

USTRUCT(BlueprintType)
struct FMotionRuleEvent
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MotionRuleEvent)
    FMotionRuleDelegate Callback;
};

UCLASS(BlueprintType, ClassGroup = (MeleeCore))
class MELEECORE_API UMotionSwitchRuleBase : public UObject, public IMotionSwitchRule
{
    GENERATED_BODY()

public:
#pragma region manage rule
    UFUNCTION(BlueprintCallable)
    void UpdateMotions(const TArray<int> & rules);

    UFUNCTION(BlueprintCallable)
    bool AddMotion(int Id);

    UFUNCTION(BlueprintCallable)
    bool RemoveMotion(int Id);

    UFUNCTION(BlueprintCallable)
    void AddRule(int id, const FMotionRuleDelegate& event);
    
    UFUNCTION(BlueprintCallable)
    void RemoveRule(int id);
#pragma endregion


#pragma region OverriderInterface
    virtual bool IsSwitchable_Implementation(int id) override;
#pragma endregion


public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<int> m_SwitchList;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<int, FMotionRuleDelegate> m_Rules;
};