#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MotionRule.h"
#include "MotionRuleBase.generated.h"

UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EMotionType : uint8
{
    NONE = 0 UMETA(Hidden),
    MOTION_TOP_PRIOR = 1 << 0 UMETA(DisplayName="Top is prior"),
    MOTION_DOWN_PRIOR = 1 << 1 UMETA(DisplayName="Down is prior"),
};

USTRUCT(BlueprintType)
struct FMotionRuleItem
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionRule)
    int Level;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionRule)
    FString Key;
};

USTRUCT(BlueprintType)
struct FMotionRuleTable : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionRule)
    EMotionType Type;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionRule)
    TArray<FMotionRuleItem> Rules;

    FMotionRuleTable()
    {
        Type = EMotionType::MOTION_DOWN_PRIOR;
    }
};

UCLASS(ClassGroup = (MeleeCore), meta = (BlueprintSpawnableComponent))
class MELEECORE_API UMotionRuleBase : public UActorComponent, public IMotionRule
{
    GENERATED_BODY()

public:
    UMotionRuleBase();

    void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    void UpdateType(EMotionType type);

    UFUNCTION(BlueprintCallable)
    bool RegistMotion(int level, const FString &key);

    UFUNCTION(BlueprintCallable)
    bool RemoveMotion(const FString &key);

    UFUNCTION(BlueprintCallable)
    bool GetLevel(const FString &key, int &outLevel);

    UFUNCTION(BlueprintCallable)
    bool UpdateMotion(const FString &Key, int newLevel);

#pragma region OverriderInterface
    virtual bool IsRuleActive_Implementation() override;
    virtual void SetRuleActive_Implementation(bool bActive) override;
    virtual bool IsSwitchable_Implementation(int type) override;
    virtual bool SwitchMotion_Implementation(int level) override;
#pragma endregion

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FMotionRuleTable m_Table;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    EMotionType m_Type;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FMotionRuleItem> m_Motions;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    int m_CurrentLevel;
};