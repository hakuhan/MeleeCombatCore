#include "Basic/Executor.h"

void UExecutor::CreateBehavior_Implementation()
{
    // Create action chain
    bool isWayOk = FindWay(m_Data.Target, m_Data.Way);

    if (!isWayOk)
    {
        m_Data.State = EExecutorState::EXECUTOR_WAITING;
    }
    else
    {
        m_Data.State = EExecutorState::EXECUTOR_READY;
        m_Data.BehaviorIndex = 0;
        m_Data.Behaviors.Reset();
    }
}

void UExecutor::UpdateBehavior_Implementation()
{
    // Checkout road
    if (m_Data.State == EExecutorState::EXECUTOR_WAITING)
    {
        bool isWayOk = FindWay(m_Data.Target, m_Data.Way);
        if (isWayOk)
        {
            m_Data.State = EExecutorState::EXECUTOR_READY;
            m_Data.BehaviorIndex = 0;
            m_Data.Behaviors.Reset();
        }
    }
    else
    {
        // TODO Check thing lose

        
        // Check state
        FActionData behavior;
        TScriptInterface<IActionInterface> action;
        if (!m_Data.GetCurrentBehavior(behavior))
        {
            return;
        }
        if (!behavior.GetCurrentAction(action))
        {
            return;
        }
        auto actionState = action->GetState();
        switch (actionState)
        {
        case EActionState::Action_Failure:
        case EActionState::Action_Unreachable:
            m_Data.State = EExecutorState::EXECUTOR_WAITING;
            action->FinishAction();
            behavior.Reset();

            // TODO Store data
            break;

        case EActionState::Action_Success:
        {
            action->FinishAction();
            // own thing
            FThing reward;
            if (m_Data.GetCurrentReward(reward))
            {
                OwnThing(reward);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Reward of action %s is lose!"), *action.GetObject()->GetName());
            }

            bool switchAction = false;
            // Switch to next action
            if (m_Data.IsLastAction())
            {
                if (m_Data.IsLastBehavior())
                {
                    m_Data.State = EExecutorState::EXECUTOR_FINISH;
                    m_Data.BehaviorIndex = 0;
                    behavior.Reset();
                }
                else
                {
                    // Switch to next behavior
                    m_Data.SwitchBehavior();
                    behavior.Reset();
                    switchAction = true;
                }
            }
            else
            {
                // Switch to next action of current behvior
                behavior.SwitchAction();
                switchAction = true;
            }

            // Switch to next action
            if (switchAction)
            {
                FBehaviorEvent nextBehaviorInfo;
                if (m_Data.GetBehaviorInfo(nextBehaviorInfo))
                {
                    FActionData nextBehavior;
                    if (!m_Data.GetCurrentBehavior(nextBehavior))
                    {
                        m_Data.Behaviors.Add(nextBehavior);
                    }
                    TScriptInterface<IActionInterface> nextAction;
                    TSubclassOf<UObject> actionClass;
                    if (m_Data.Way.GetActionClass(m_Data.BehaviorIndex, nextBehavior.ActionIndex, actionClass))
                    {
                        if (CreateAction(nextAction, actionClass))
                        {
                            nextAction->PrepareAction();
                            if (nextAction->IsCost())
                            {
                                // decrease thing
                                UseThing(nextBehaviorInfo.Condition);
                            }
                        }
                        else
                        {
                            UE_LOG(LogTemp, Error, TEXT("Switch next action failed, Create action by class failed!"))
                        }
                    }
                    else
                    {
                        UE_LOG(LogTemp, Error, TEXT("Switch next action failed, Action index out of range!"))
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Cannot get next behavior"))
                }
            }
        }

        break;
        }
    }
}

void UExecutor::ExecuteBehavior_Implementation()
{
    if (m_Data.State == EExecutorState::EXECUTOR_READY || m_Data.State == EExecutorState::EXECUTOR_EXECUTING)
    {
        FBehaviorEvent behaviorInfo;
        if (m_Data.GetBehaviorInfo(behaviorInfo))
        {
            FActionData behavior;
            TScriptInterface<IActionInterface> action;
            if (m_Data.BehaviorIndex >= m_Data.Behaviors.Num())
            {
                CreateAction(action, behaviorInfo.ActionSequenceClasses[0]);
            }
            else
            {
                m_Data.Behaviors[m_Data.BehaviorIndex].GetCurrentAction(action);
            }

            // Execute action
            if (action != nullptr)
            {
                action->RunningAction();
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("%s's Action haven't been created!"), *behaviorInfo.Name)
            }
        }
    }
}

void UExecutor::Stop()
{
    if (m_Data.State == EExecutorState::EXECUTOR_EXECUTING)
    {
        TScriptInterface<IActionInterface> action;
        m_Data.Behaviors[m_Data.BehaviorIndex].GetCurrentAction(action);
        if (action != nullptr)
        {
            action->FinishAction();
        }
    }
}

EExecutorState UExecutor::GetExecuteState_Implementation()
{
    return EExecutorState::EXECUTOR_READY;
}

bool UExecutor::FindWay_Implementation(FThing target, FWay &way)
{
    way.Empty();

    TArray<FWay> ways;
    if (GetAllWays(target, ways))
    {
        int cost = ways[0].GetCost();
        way = ways[0];

        for (auto tempWay : ways)
        {
            if (cost > tempWay.GetCost())
            {
                cost = tempWay.GetCost();
                way = tempWay;
            }
        }

        return true;
    }

    return false;
}

bool UExecutor::GetAllWays(FThing target, TArray<FWay> &ways)
{
    ways.Empty();
    bool gotAllWays = false;
    TArray<FWay> allSituations;
    TArray<FBehaviorEvent> firstSituation;
    if (GetAllSituation(target, firstSituation, FBehaviorEvent::EmptyBehavior()))
    {
        // Get all situation of main target
        AddSituation(allSituations, firstSituation);

        // Find situations of children
        while (!gotAllWays)
        {
            if (allSituations.Num() > 0)
            {
                // Check and remove situation one by one
                auto tempWay = allSituations.Pop();

                FThing condition;
                bool hasCondition = tempWay.GetLastCondition(condition);
                if (hasCondition && condition != FThing::EmptyThing())
                {
                    TArray<FBehaviorEvent> tempSituations;
                    if (GetAllSituation(condition, tempSituations, tempWay.Behaviors[tempWay.Behaviors.Num() - 1]))
                    {
                        AddSituation(allSituations, tempSituations, tempWay);
                    }
                }
                else
                {
                    ways.Add(tempWay);
                }
            }
            else
            {
                gotAllWays = true;
            }
        }
    }

    return ways.Num() > 0;
}

bool UExecutor::GetAllSituation(FThing target, TArray<FBehaviorEvent> &situation, const FBehaviorEvent &excludeBehavior)
{
    situation.Empty();
    for (int i = 0; i < TotalBehaviors.Num(); ++i)
    {
        if (TotalBehaviors[i].Reward == target && TotalBehaviors[i] != excludeBehavior)
        {
            situation.AddUnique(TotalBehaviors[i]);
        }
    }
    return situation.Num() >= 0;
}

void UExecutor::AddSituation(TArray<FWay> &Total, TArray<FBehaviorEvent> situations, FWay preCondition)
{
    for (auto behavior : situations)
    {
        TArray<FBehaviorEvent> behaviors;
        behaviors.Append(preCondition.Behaviors);
        behaviors.Add(behavior);
        Total.Add(behaviors);
    }
}

bool UExecutor::CreateAction(TScriptInterface<IActionInterface> &action, TSubclassOf<UObject> actionClass)
{
    bool result = false;
    UObject *actionObj = NewObject<UObject>(this, actionClass);
    if (actionObj)
    {
        action.SetInterface(dynamic_cast<IActionInterface *>(actionObj));
        action.SetObject(actionObj);
        action->Init(m_Mind->GetOwner());

        FActionData behavior;
        if (!m_Data.GetCurrentBehavior(behavior))
        {
            m_Data.Behaviors.Add(behavior);
        }
        behavior.AddAction(action);
        result = true;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Executor create action failed!"));
    }

    return result;
}