#pragma once

#include "CoreMinimal.h"
#include "Structure/Thing.h"
#include "Core/ActionInterface.h"
#include "Core/BehaviorExecutorInterface.h"
#include "Structure/DataTableRows.h"
#include "ExecutorItem.generated.h"

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
struct MINDCORE_API FExecutorItem
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

    friend bool operator==(const FExecutorItem& Lhs, const FExecutorItem& Rhs)
    {
        return Lhs.Name == Rhs.Name && Lhs.precondition == Rhs.precondition && Lhs.Reward == Rhs.Reward;
    }

    friend bool operator!=(const FExecutorItem& Lhs, const FExecutorItem& Rhs)
    {
        return !(Lhs == Rhs);
    }

    FExecutorItem()
        : Name("Empty")
        , precondition()
        , Reward()
        , Cost(EActionCost::BEHAVIOR_NONE)
        , ActionSequenceClasses()
    { }

    static FExecutorItem EmptyBehavior()
    {
        return FExecutorItem();
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