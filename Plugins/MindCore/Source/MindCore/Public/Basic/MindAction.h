#pragma once

#include "CoreMinimal.h"
#include "Core/ActionInterface.h"
#include "MindAction.generated.h"

DECLARE_DELEGATE_TwoParams(FUpdateDifficultyDelegate, UMindAction*, EActionDifficulty)

UCLASS(Blueprintable)
class MINDCORE_API UMindAction : public UObject, public IActionInterface
{
    GENERATED_BODY()

public:
	UMindAction()
	{
		m_State = EActionState::Action_Inactive;
		m_bLose = false;
	}

	void Init_Implementation(AActor* owner) override
	{
		m_Owner = owner;
	}


	bool IsCost_Implementation() override
	{
		return true;
	}

#pragma region events

	void PrepareAction_Implementation() override
	{
		
	}


	void RunningAction_Implementation() override
	{
		
	}


	void FinishAction_Implementation() override
	{
		
	}

	void OnLose_Implementation() override
	{
		
	}

	void UpdateDifficulty_Implementation(EActionDifficulty difficulty)
	{
		OnUpdateDifficulty.ExecuteIfBound(this, difficulty);
	}
#pragma endregion events

	EActionState GetState_Implementation() override
	{
		return m_State;
	}


	bool CanEfficacyLose_Implementation() override
	{
		return false;
	}


	bool CheckLose_Implementation() override
	{
		return m_bLose;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	EActionState m_State;
	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	AActor* m_Owner;
	UPROPERTY(BlueprintReadwrite)
	bool m_bLose;

	FUpdateDifficultyDelegate OnUpdateDifficulty;

};