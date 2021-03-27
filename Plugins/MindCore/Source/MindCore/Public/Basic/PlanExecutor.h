/*
    Author: baihan 
    Date: "2021-03-16" 
    Description: This class will Automatically find best action to get wishes
*/

#pragma once

#include "CoreMinimal.h"
#include "Basic/Executor.h"
#include "Structure/ExecutorInfo.h"
#include "Core/ActionInterface.h"
#include "PlanExecutor.generated.h"

UCLASS(Blueprintable)
class MINDCORE_API UplanItem : public UExecutorItem
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    TArray<FThing> Preconditions;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    TArray<FThing> Targets;
};

UCLASS(Blueprintable)
class MINDCORE_API UPlanExecutor : public UExecutor
{
    GENERATED_BODY()

public:
    virtual void CreateBehavior_Implementation() override;
    virtual void UpdateBehavior_Implementation() override;
    virtual void ExecuteBehavior_Implementation() override;
    virtual void GetExecuteState_Implementation() override;
};