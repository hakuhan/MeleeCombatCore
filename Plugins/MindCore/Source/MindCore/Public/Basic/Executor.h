#pragma once

#include "CoreMinimal.h"
#include "Core/BehaviorExecutorInterface.h"
#include "Core/ActionInterface.h"
#include "Basic/Mind.h"
#include "Structure/BehaviorEvent.h"
#include "Structure/Thing.h"
#include "Executor.generated.h"

class UMind;
DECLARE_DELEGATE_OneParam(FObtainThingDelegate, const FThing &)
DECLARE_DELEGATE_OneParam(FUseThingDelegate, const FThing &)

USTRUCT(BlueprintType)
struct FWay
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FBehaviorEvent> Behaviors;

    FWay()
    { }

    FWay(TArray<FBehaviorEvent> hehavior)
        : Behaviors(hehavior)
    { }

    void Empty()
    {
        Behaviors.Empty();
    }

    bool GetLastCondition(FThing& outCondition)
    {
        if (Behaviors.Num() > 0)
        {
            outCondition = Behaviors[Behaviors.Num() - 1].Condition;
        }
        return Behaviors.Num() > 0;
    }

    bool GetBehavior(int index, FBehaviorEvent& outBehavior)
    {
        if (index < Behaviors.Num() && index >= 0)
        {
            outBehavior = Behaviors[index];
            return true;
        }

        return false;
    }

    bool IsLastBehavior(int index)
    {
        return index == Behaviors.Num() - 1;
    }

    bool IsLastAction(int behaviorIndex, int actionIndex)
    {
        if (behaviorIndex >= Behaviors.Num())
        {
            UE_LOG(LogTemp, Error, TEXT("Behavior index out of range when tring to find action of target behavior"))
            return true;
        }
        return Behaviors[behaviorIndex].ActionSequenceClasses.Num() == actionIndex;
    }

    bool GetActionClass(int behaviorIndex, int actionIndex, TSubclassOf<UObject>& outClass)
    {
        if (behaviorIndex >=0 && behaviorIndex < Behaviors.Num())
        {
            if (actionIndex >= 0 && actionIndex < Behaviors[behaviorIndex].ActionSequenceClasses.Num())
            {
                outClass = Behaviors[behaviorIndex].ActionSequenceClasses[actionIndex];
                return true;
            }
        }

        return false;
    }

    int GetCost()
    {
        int cost = 0;

        for (int i = 0; i < Behaviors.Num(); ++i)
        {
            cost += (int)Behaviors[i].Cost;
        }

        return cost;
    }

    friend bool operator==(const FWay& l, const FWay& r)
    {
        return l.Behaviors == r.Behaviors;
    }
};

USTRUCT(BlueprintType)
struct FActionData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    TArray<TScriptInterface<IActionInterface>> Actions;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int ActionIndex;

    void Reset()
    {
        ActionIndex = 0;
    }

    void SwitchAction()
    {
        ActionIndex++;
    }

    void AddAction(TScriptInterface<IActionInterface> action)
    {
        Actions.Add(action);
    }

    bool GetCurrentAction(TScriptInterface<IActionInterface>& action)
    {
        if (ActionIndex >= 0 && ActionIndex < Actions.Num())
        {
            action = Actions[ActionIndex];
            return true;
        }

        return false;
    }
};

USTRUCT(BlueprintType) 
struct FExecutorData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
    FThing Target;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FWay Way;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    EExecutorState State;
    UPROPERTY(BlueprintReadwrite)
    TArray<FActionData> Behaviors;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int BehaviorIndex;

    bool GetCurrentBehavior(FActionData& outBehavior)
    {
        if (BehaviorIndex >= 0 && BehaviorIndex < Behaviors.Num())
        {
            outBehavior = Behaviors[BehaviorIndex];
            return true;
        }

        return false;
    }

    bool GetBehaviorInfo(FBehaviorEvent& outInfo)
    {
        return Way.GetBehavior(BehaviorIndex, outInfo);
    }

    bool SwitchBehavior()
    {
        if (!IsLastBehavior())
        {
            BehaviorIndex++;

            // Create behavior if needed
            if (BehaviorIndex >= Behaviors.Num())
            {
                Behaviors.Add(FActionData());
            }
            return true;
        }

        return false;
    }

    bool IsLastBehavior()
    {
        return Way.IsLastBehavior(BehaviorIndex);
    }

    bool IsLastAction()
    {
        FActionData behavior;
        if (GetCurrentBehavior(behavior))
        {
            return Way.IsLastAction(BehaviorIndex, behavior.ActionIndex);
        }

        return false;
    }

    bool GetCurrentReward(FThing& outReward)
    {
        FBehaviorEvent info;
        if (GetBehaviorInfo(info))
        {
            outReward = info.Reward;
        }

        return false;
    }
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
    TArray<FBehaviorEvent> TotalBehaviors;

    FObtainThingDelegate OnObtainThing;
    FUseThingDelegate OnUseThing;

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
    void OwnThing(const FThing &thing)
    {
        OnObtainThing.ExecuteIfBound(thing);
    }

    UFUNCTION(BlueprintCallable)
    void UseThing(const FThing &thing)
    {
        OnUseThing.ExecuteIfBound(thing);
    }

    // Find best way to reach target
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool FindWay(FThing target, FWay& ways);
    virtual bool FindWay_Implementation(FThing target, FWay& way);
    // Get all ways of target
    UFUNCTION(BlueprintCallable)
    bool GetAllWays(FThing target, TArray<FWay>& ways);
    // Get all situation of one target directly
    UFUNCTION(BlueprintCallable)
    bool GetAllSituation(FThing target, TArray<FBehaviorEvent>& situation, const FBehaviorEvent& excludeBehavior);
    void AddSituation(TArray<FWay>& Total, TArray<FBehaviorEvent> situations, FWay preCondition = FWay());
    
    #pragma region action
    UFUNCTION(BlueprintCallable)
    bool CreateAction(TScriptInterface<IActionInterface>& action, TSubclassOf<UObject> actionClass);

    #pragma endregion

#pragma region IExecutor implement
    virtual void CreateBehavior_Implementation() override;
    virtual void UpdateBehavior_Implementation() override;
    virtual void ExecuteBehavior_Implementation() override;
    virtual EExecutorState GetExecuteState_Implementation() override;
#pragma endregion
};