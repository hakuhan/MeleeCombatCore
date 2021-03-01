#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillComponent/SkillLineInfo.h"
#include "SkillComponent/Skill.h"
#include "SkillComponent/SkillLine.h"
#include "SkillComponent/SkillDynamicData.h"
#include "SkillComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(OnSkillEndDelegate, FString)

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

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
		TArray<FSkillLineInfo> SkillLines;
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

	FSkillComponentData(bool bDebug)
	{
		DynamicData = NewObject<ASkillDynamicData>();
		DynamicData->bDebug = bDebug;
	}
};

UCLASS(Blueprintable, ClassGroup = (MeleeCore))
class MELEECORE_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		bool m_debug = false;
	UPROPERTY(BlueprintReadWrite)
		FSkillTable m_Info;
protected:
	UPROPERTY()
		USkillLine* m_LineControl;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FSkillComponentData m_Data;

public:
	void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void InitInfo();

#pragma region Execute
	// Execute current line skill
	UFUNCTION(BlueprintCallable)
		bool ExecuteSkill();
#pragma endregion

#pragma region Switch
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "skillName"))
		bool SwitchSkill(const FString& lineName, const FString& skillName, bool bForce = false);
#pragma endregion

#pragma region switch conditions
	UFUNCTION(BlueprintCallable)
		bool IsExecuting();

	UFUNCTION(BlueprintCallable)
		bool CanSwitchFrom(const TArray<FString>& limitedList, bool fromAnySkill = false);

	UFUNCTION(BlueprintCallable)
		bool IsCurrentSkillLine(const FString& lineName);

	// It's used in the hold line of skillComponent, skillLine and skill at run time
	ASkillDynamicData* GetDynamicData()
	{
		return m_Data.DynamicData;
	}
#pragma endregion

#pragma region End skill
	UFUNCTION(BlueprintCallable)
		void StopSkill(bool bRule, const FAlphaBlend& InBlendOut);

	OnSkillEndDelegate OnSkllEndEvent;

	// For notify
	UFUNCTION(BlueprintImplementableEvent)
		void OnSkillEnded(const FString& SkillLineName);

	// Be noticed by end notify
	void SkillEnded();
#pragma endregion

protected:
	void OnSkillUpdate(ESkillLineState lineState);

};