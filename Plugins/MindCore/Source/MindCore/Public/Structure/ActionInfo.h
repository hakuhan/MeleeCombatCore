#pragma once

#include "CoreMinimal.h"
#include "Structure/Thing.h"
#include "Core/ActionInterface.h"
#include "Core/BehaviorExecutorInterface.h"
#include "Structure/DataTableRows.h"
#include "ActionInfo.generated.h"

UENUM(BlueprintType)
enum class EActionCost : uint8
{
    BEHAVIOR_NONE = 0 UMETA(DisplayName="None"),
    BEHAVIOR_EASY UMETA(DisplayName="Easy"),
    BEHAVIOR_NORMAL UMETA(DisplayName="Normal"),
    BEHAVIOR_HARD UMETA(DisplayName="Hard"),
    BEHAVIOR_DIFFICULT UMETA(DisplayName="Difficult"),
};

USTRUCT(BlueprintType)
struct MINDCORE_API FActionInfo : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    FDataTableRows precondition;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    FDataTableRows Reward;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    EActionCost Cost;
    UPROPERTY(EditAnywhere, BlueprintReadwrite, meta = (MustImplement = "ActionInterface"))
    TArray<TSubclassOf<UObject>> ActionSequenceClasses;

    friend bool operator==(const FActionInfo& Lhs, const FActionInfo& Rhs)
    {
        return Lhs.Name == Rhs.Name && Lhs.precondition == Rhs.precondition && Lhs.Reward == Rhs.Reward;
    }

    friend bool operator!=(const FActionInfo& Lhs, const FActionInfo& Rhs)
    {
        return !(Lhs == Rhs);
    }

    FActionInfo()
        : Name("Empty")
        , precondition()
        , Reward()
        , Cost(EActionCost::BEHAVIOR_NONE)
        , ActionSequenceClasses()
    { }

    static FActionInfo EmptyBehavior()
    {
        return FActionInfo();
    }

    bool IsNeedsMatched(const FDataTableRows& goal) const
    {
        bool result = false;
        if (Reward.DataTable == goal.DataTable)
        {
            for (FName row : Reward.Rows)
            {
                if (goal.Rows.Contains(row))
                {
                    result = true;
                    break;
                }
            }
        }

        return result;
    }

    bool IsNeedsMatched(const FName& goal) const
    {
        return Reward.Rows.Contains(goal);
    }
};