#pragma once

#include "CoreMinimal.h"
#include "Thing.h "
#include "Core/ActionInterface.h"
#include "Core/BehaviorExecutorInterface.h"
#include "BehaviorEvent.generated.h"

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
    UPROPERTY(EditAnywhere, BlueprintReadwrite, meta = (MustImplement = "ActionInterface"))
    TArray<TSubclassOf<UObject>> ActionSequenceClasses;

    friend bool operator==(const FBehaviorEvent& Lhs, const FBehaviorEvent& Rhs)
    {
        return Lhs.Name == Rhs.Name && Lhs.Condition == Rhs.Condition && Lhs.Reward == Rhs.Reward;
    }
};