#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MotionRule.h"
#include "MotionRuleBase.generated.h"

UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EMotionType : uint8
{
    NONE = 0 UMETA(Hidden),
    MOTION_TOP_PRIOR = 1 << 0 UMETA(DisplayName = "Top is prior"),
    MOTION_DOWN_PRIOR = 1 << 1 UMETA(DisplayName = "Down is prior"),
};

UCLASS(BlueprintType, ClassGroup = (MeleeCore))
class MELEECORE_API UMotionRuleBase : public UObject, public IMotionRule
{
    GENERATED_BODY()

public:
    UMotionRuleBase();

    UFUNCTION(BlueprintCallable)
    void UpdateType(EMotionType type);

#pragma region manage rule
    UFUNCTION(BlueprintCallable)
    void RegistRules(const TMap<int, int> & rules);

    UFUNCTION(BlueprintCallable)
    bool RegistMotion(int level, int Id);

    UFUNCTION(BlueprintCallable)
    bool RemoveMotion(int Id);

    UFUNCTION(BlueprintCallable)
    void EmptyRules();

    UFUNCTION(BlueprintCallable)
    bool UpdateMotion(int Id, int newLevel);
#pragma endregion


#pragma region OverriderInterface
    virtual bool IsSwitchable_Implementation(int id) override;
    virtual bool SwitchMotion_Implementation(int id) override;
    virtual void AddCheckEvent_Implementation(int id, const FMotionRuleDelegate& event) override;
    virtual void RemoveCheckEvent_Implementation(int id);
#pragma endregion

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    EMotionType m_Type;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<int, int> m_Rules;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<int, FMotionRuleDelegate> m_ExtendRules;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    int m_CurrentId;
};