#pragma once

#include "CoreMinimal.h"
#include "Core/BehaviorExecutorInterface.h"
#include "Core/ActionInterface.h"
#include "Basic/Mind.h"
#include "Structure/BehaviorEvent.h"
#include "Executor.generated.h"

class UMind;
DECLARE_DELEGATE_OneParam(FObtainThingDelegate, const TArray<FThing> &)

USTRUCT(BlueprintType) 
struct FExecutorData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
    FThing Target;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    TArray<FBehaviorEvent> Ways;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    EExecutorState State;
    UPROPERTY(BlueprintReadwrite)
    TArray<TScriptInterface<IActionInterface>> Actions;
    UPROPERTY(BlueprintReadwrite)
    bool bNeedRefreshActions;
};

UCLASS(Blueprintable)
class MINDCORE_API UExecutor : public UObject, public IBehaviorExecutorInterface
{
    GENERATED_BODY()
public:
    UPROPERTY()
    UMind* m_Mind;
    UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
    FExecutorData m_Data;
    UPROPERTY(BlueprintReadWrite)
    TArray<FBehaviorEvent> Behaviors;

    FObtainThingDelegate OnObtainThings;

    UFUNCTION(BlueprintNativeEvent)
    void Init(const FThing &thing, UMind* mind);
    virtual void Init_Implementation(const FThing &thing, UMind* mind)
    {
        m_Data.Target = thing;
        m_Data.State = EExecutorState::EXECUTOR_WAITING;
        m_Mind = mind;
    }

    virtual void Stop();

    UFUNCTION(BlueprintCallable)
    void OnOwnThing(const TArray<FThing> &things)
    {
        OnObtainThings.ExecuteIfBound(things);
    }

    // Find a way to reach target
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool FindWay(FThing target, TArray<FBehaviorEvent>& ways);
    // virtual bool FindWay(FThing target, TArray<FBehaviorEvent>& ways);

#pragma region IExecutor implement
    virtual void CreateBehavior_Implementation() override;
    virtual void UpdateBehavior_Implementation() override;
    virtual void ExecuteBehavior_Implementation() override;
    virtual EExecutorState GetExecuteState_Implementation() override;
#pragma endregion
};