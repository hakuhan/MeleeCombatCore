#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillComponent/SkillLineInfo.h"
#include "SkillComponent/Skill.h"
#include "SkillComponent/SkillLine.h"
#include "SkillComponent.generated.h"

class ASkillDynamicData;

UENUM(BlueprintType)
enum class ESkillState : uint8
{
    SKILL_UNSTART = 0 UMETA(DisplayName = "未开始"),
    SKILL_EXECUTING UMETA(DisplayName = "执行中"),
    SKILL_TERMINAl UMETA(DisplayName = "终止"),
};

USTRUCT(BlueprintType)
struct FSkillTable : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Skill)
    TArray<FSkillLineInfo> SkillLines;

    FSkillTable() {}

    FSkillTable(const FSkillTable& other)
    {
        SkillLines = other.SkillLines;
    }
};

USTRUCT(BlueprintType)
struct FSkillComponentData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int LineIndex = -1;
    UPROPERTY(BlueprintReadOnly)
    ESkillState State = ESkillState::SKILL_UNSTART;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ASkillDynamicData* DynamicData;

    FSkillComponentData() 
    {
        DynamicData = NewObject<ASkillDynamicData>();
    }
};

UCLASS(ClassGroup=(XComponent), meta=(BlueprintSpawnableComponent))
class MELEECORE_API USkillComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FDataTableRowHandle m_InfoTable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FSkillTable m_Info;
protected:
    UPROPERTY()
    USkillLine* m_LineControl;
    UPROPERTY(BlueprintReadWrite)
    FSkillComponentData m_Data;

public:
    void BeginPlay() override;
	void BeginDestroy() override;

    UFUNCTION(BlueprintCallable)
    bool ExecuteSkill();

    UFUNCTION(BlueprintCallable)
    bool IsExecuting();

    UFUNCTION(BlueprintCallable)
    void StopSkill(bool terminate, const FAlphaBlend& InBlendOut);

    UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "skillName"))
    bool SwitchSkillWithRule(const FString& lineName, const FString& skillName);

    UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "skillName"))
    bool SwitchSkill(const FString& lineName, const FString& skillName);

    UFUNCTION(BlueprintCallable)
    bool IsCurrentSkillLine(const FString& lineName);

    ASkillDynamicData* GetDynamicData()
    {
        return m_Data.DynamicData;
    }



protected:
    void OnSkillUpdate(ESkillLineState lineState);

};