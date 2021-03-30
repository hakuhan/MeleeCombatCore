#pragma once

#include "CoreMinimal.h"
#include "Core/BehaviorExecutorInterface.h"
#include "Core/ActionInterface.h"
#include "Executor.generated.h"

DECLARE_DELEGATE_OneParam(FObtainThingDelegate, const TArray<FThing>&)

UENUM(BlueprintType)
enum class EExecuteType : uint8
{
    EXECUTE_ACTION UMETA(DisplayName="Action"),
    EXECUTE_EXECUTOR UMETA(DisplayName="Executor"),
};

USTRUCT(BlueprintType)
struct MINDCORE_API FBehaviorEvent
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    TArray<FThing> Conditions;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    TArray<FThing> Rewards;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    EExecuteType ExecuteType;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    TArray<TScriptInterface<IActionInterface>> ActionSequence;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    TScriptInterface<IBehaviorExecutorInterface> Executor;
};

USTRUCT(BlueprintType)
struct FExecutorData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Executor)
    TArray<FBehaviorEvent> BehaviorList;
};

UCLASS(Blueprintable)
class MINDCORE_API UExecutor : public UObject, public IBehaviorExecutorInterface
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    FThing Target;
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    FExecutorData m_Data;

    FObtainThingDelegate OnObtainThings;

    virtual void Init(const FThing& thing)
    {
        Target = thing;
    }

    virtual void Stop();

    UFUNCTION(BlueprintCallable)
    void OnOwnThing(const TArray<FThing>& things)
    {
        OnObtainThings.ExecuteIfBound(things);
    }

    virtual void CreateBehavior_Implementation() override;
    virtual void UpdateBehavior_Implementation() override;
    virtual void ExecuteBehavior_Implementation() override;
    virtual EExecutorState GetExecuteState_Implementation() override;
};