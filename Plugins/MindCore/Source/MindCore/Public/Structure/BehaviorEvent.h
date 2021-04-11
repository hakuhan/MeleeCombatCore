#pragma once

#include "CoreMinimal.h"
#include "Structure/Thing.h"
#include "Core/ActionInterface.h"
#include "Core/BehaviorExecutorInterface.h"
#include "BehaviorEvent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorEventCost : uint8
{
    BEHAVIOR_NONE = 0 UMETA(DisplayName="None"),
    BEHAVIOR_EASY UMETA(DisplayName="Easy"),
    BEHAVIOR_NORMAL UMETA(DisplayName="Normal"),
    BEHAVIOR_HARD UMETA(DisplayName="Hard"),
    BEHAVIOR_DIFFICULT UMETA(DisplayName="Difficult"),
};

USTRUCT(BlueprintType)
struct MINDCORE_API FBehaviorEvent
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    FThing Condition;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    FThing Reward;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    EBehaviorEventCost Cost;
    UPROPERTY(EditAnywhere, BlueprintReadwrite, meta = (MustImplement = "ActionInterface"))
    TArray<TSubclassOf<UObject>> ActionSequenceClasses;

    friend bool operator==(const FBehaviorEvent& Lhs, const FBehaviorEvent& Rhs)
    {
        return Lhs.Name == Rhs.Name && Lhs.Condition == Rhs.Condition && Lhs.Reward == Rhs.Reward;
    }

    friend bool operator!=(const FBehaviorEvent& Lhs, const FBehaviorEvent& Rhs)
    {
        return !(Lhs == Rhs);
    }

    FBehaviorEvent()
        : Name("Empty")
        , Condition(FThing::EmptyThing())
        , Reward(FThing::EmptyThing())
        , Cost(EBehaviorEventCost::BEHAVIOR_NONE)
        , ActionSequenceClasses()
    { }

    static FBehaviorEvent EmptyBehavior()
    {
        return FBehaviorEvent();
    }
};