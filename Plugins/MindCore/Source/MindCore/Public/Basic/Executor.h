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
    TArray<FBehaviorEvent> ActionInfos;

    FWay()
    { }

    FWay(TArray<FBehaviorEvent> hehavior)
        : ActionInfos(hehavior)
    { }

    void Empty()
    {
        ActionInfos.Empty();
    }

    bool GetLastCondition(FThing& outCondition)
    {
        if (ActionInfos.Num() > 0)
        {
            outCondition = ActionInfos[ActionInfos.Num() - 1].Condition;
        }
        return ActionInfos.Num() > 0;
    }

    bool GetActionInfo(int index, FBehaviorEvent& outAction)
    {
        if (index < ActionInfos.Num() && index >= 0)
        {
            outAction = ActionInfos[index];
            return true;
        }

        return false;
    }

    bool IsLastAction(int index)
    {
        return index == ActionInfos.Num() - 1;
    }

    bool IsLastActionItem(int actionIndex, int actionItemIndex)
    {
        if (actionIndex >= ActionInfos.Num())
        {
            UE_LOG(LogTemp, Error, TEXT("Behavior index out of range when tring to find action of target behavior"))
            return true;
        }
        return ActionInfos[actionIndex].ActionSequenceClasses.Num() == actionItemIndex;
    }

    bool GetActionClass(int actionIndex, int actionItemIndex, TSubclassOf<UObject>& outClass)
    {
        if (actionIndex >=0 && actionIndex < ActionInfos.Num())
        {
            if (actionItemIndex >= 0 && actionItemIndex < ActionInfos[actionIndex].ActionSequenceClasses.Num())
            {
                outClass = ActionInfos[actionIndex].ActionSequenceClasses[actionItemIndex];
                return true;
            }
        }

        return false;
    }

    int GetCost()
    {
        int cost = 0;

        for (int i = 0; i < ActionInfos.Num(); ++i)
        {
            cost += (int)ActionInfos[i].Cost;
        }

        return cost;
    }

    friend bool operator==(const FWay& l, const FWay& r)
    {
        return l.ActionInfos == r.ActionInfos;
    }
};

USTRUCT(BlueprintType)
struct FActionData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    TArray<TScriptInterface<IActionInterface>> Items;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int ActionItemIndex;

    void Reset()
    {
        ActionItemIndex = 0;
    }

    void SwitchActionItemIndex()
    {
        ActionItemIndex++;
    }

    void AddActionItem(TScriptInterface<IActionInterface> item)
    {
        Items.Add(item);
    }

    bool GetCurrentActionItem(TScriptInterface<IActionInterface>& item, bool autoCreate = true)
    {
        if (ActionItemIndex >= 0 && ActionItemIndex < Items.Num())
        {
            item = Items[ActionItemIndex];
            return true;
        }
        else if (autoCreate && ActionItemIndex == Items.Num())
        {
            item = TScriptInterface<IActionInterface>();
            Items.Add(item);
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
    TArray<FActionData> Actions;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int ActionIndex;

    bool GetCurrentAction(FActionData& outAction, bool autoCreate = true)
    {
        if (ActionIndex >= 0 && ActionIndex < Actions.Num())
        {
            outAction = Actions[ActionIndex];
            return true;
        }
        else if (autoCreate && ActionIndex == Actions.Num())
        {
            outAction = FActionData();
            Actions.Add(outAction);
            return true;
        }

        return false;
    }

    bool GetActionInfo(FBehaviorEvent& outInfo)
    {
        return Way.GetActionInfo(ActionIndex, outInfo);
    }

    bool SwitchAction()
    {
        if (!IsLastAction())
        {
            ActionIndex++;

            // Create behavior if needed
            if (ActionIndex >= Actions.Num())
            {
                Actions.Add(FActionData());
            }
            return true;
        }

        return false;
    }

    bool IsLastAction()
    {
        return Way.IsLastAction(ActionIndex);
    }

    bool IsLastActionItem()
    {
        FActionData behavior;
        if (GetCurrentAction(behavior))
        {
            return Way.IsLastActionItem(ActionIndex, behavior.ActionItemIndex);
        }

        return false;
    }

    bool GetCurrentReward(FThing& outReward)
    {
        FBehaviorEvent info;
        if (GetActionInfo(info))
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
    TArray<FBehaviorEvent> TotalActionInfos;

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
    bool GetAllSituation(FThing target, TArray<FBehaviorEvent>& situation, const FBehaviorEvent& excludeAction);
    void AddSituation(TArray<FWay>& Total, TArray<FBehaviorEvent> situations, FWay preCondition = FWay());
    
    #pragma region action
    UFUNCTION(BlueprintCallable)
    bool CreateActionItem(TScriptInterface<IActionInterface>& action, TSubclassOf<UObject> actionClass);

    #pragma endregion

#pragma region IExecutor implement
    virtual void CreateBehavior_Implementation() override;
    virtual void UpdateBehavior_Implementation() override;
    virtual void ExecuteBehavior_Implementation() override;
    virtual EExecutorState GetExecuteState_Implementation() override;
#pragma endregion
};