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
    void UpdateAllMotions(const TArray<int>& motions);

    UFUNCTION(BlueprintCallable)
    bool AddMotion(int Id);

    UFUNCTION(BlueprintCallable)
    void RemoveMotion(int Id);

    UFUNCTION(BlueprintCallable)
    void UpdateAlternativeRules(const TMap<int, FMotionRuleEvent>& rules);

    UFUNCTION(BlueprintCallable)
    void UpdateBasicRule(int id, const FMotionRuleDelegate& event);
    
    UFUNCTION(BlueprintCallable)
    void RemoveBasicRule(int id);
#pragma endregion


#pragma region OverriderInterface
    virtual bool IsSwitchable_Implementation(int id) override;
    
    UFUNCTION(BlueprintCallable)
    bool CheckMotion(int id);

    UFUNCTION(BlueprintCallable)
    bool CheckRule(int id);
#pragma endregion


public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<int> m_SwitchList;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<int, FMotionRuleDelegate> m_BasicRules;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<int, FMotionRuleDelegate> m_AlternativeRules;

};