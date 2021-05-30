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
    FDataTableRows PreconditionTable;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    FDataTableRows RewardTable;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    EActionCost Cost;
    UPROPERTY(EditAnywhere, BlueprintReadwrite, meta = (MustImplement = "ActionInterface"))
    TArray<TSubclassOf<UObject>> ActionSequenceClasses;

    friend bool operator==(const FActionInfo& Lhs, const FActionInfo& Rhs)
    {
        return Lhs.Name == Rhs.Name && Lhs.PreconditionTable == Rhs.PreconditionTable && Lhs.RewardTable == Rhs.RewardTable;
    }

    friend bool operator!=(const FActionInfo& Lhs, const FActionInfo& Rhs)
    {
        return !(Lhs == Rhs);
    }

    FActionInfo()
        : Name("Empty")
        , PreconditionTable()
        , RewardTable()
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
        if (RewardTable.DataTable == goal.DataTable)
        {
            for (FName row : RewardTable.Rows)
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
        return RewardTable.Rows.Contains(goal);
    }
};