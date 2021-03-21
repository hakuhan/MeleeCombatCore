#pragma once

#include "CoreMinimal.h"
#include "Structure/Thing.h"
#include "Core/ActionInterface.h"
#include "Core/BehaviorExecutorInterface.h"
#include "ExecutorInfo.generated.h"

UENUM(BlueprintType)
enum class EExecuteType : uint8
{
    EXECUTE_ACTION UMETA(DisplayName="Action"),
    EXECUTE_EXECUTOR UMETA(DisplayName="Executor"),
};

UENUM(BlueprintType)
enum class EExecuteState : uint8
{
    EXECUTE_STATE_READY UMETA(DisplayName="Ready"),
    EXECUTE_STATE_EXECUTING UMETA(DisplayName="Executing"),
    EXECUTE_STATE_SUCCESS UMETA(DisplayName="Success"),
    EXECUTE_STATE_FAILURE UMETA(DisplayName="Failure"),
};

UCLASS(Blueprintable)
class MINDCORE_API UExecutorItem : public UThing
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    EExecuteType ExecuteType;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    TScriptInterface<IActionInterface> Action;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    TScriptInterface<IBehaviorExecutorInterface> Executor;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    EExecuteState State;
};

UCLASS(Blueprintable)
class MINDCORE_API UExecutorInfo : public UThing
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    UThing* Target;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    TArray<UExecutorItem*> ExecuteList;
};