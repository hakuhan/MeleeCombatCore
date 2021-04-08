#include "Basic/Executor.h"

void UExecutor::CreateBehavior_Implementation()
{
    // Create actionItem chain
    bool isWayOk = FindWay(m_Data.Target, m_Data.Way);

    if (!isWayOk)
    {
        m_Data.State = EExecutorState::EXECUTOR_WAITING;
    }
    else
    {
        m_Data.State = EExecutorState::EXECUTOR_READY;
        m_Data.ActionIndex = 0;
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
            m_Data.ActionIndex = 0;
        }
    }
    else
    {
        // Check thing lose
        for (int i = 0; i < m_Data.Actions.Num(); ++i)
        {
            auto reward = m_Data.Way.ActionInfos[i].Reward;
            for (int j = 0; j < m_Data.Actions[i].Items.Num(); ++j)
            {
                auto actionItem = m_Data.Actions[i].Items[j];
                if (actionItem->GetState() == EActionState::Action_Success
                    && m_Mind->Wish->CheckThingOwned(reward)
                    && actionItem->CanEfficacyLose()
                    && actionItem->CheckLose())
                {
                    UseThing(reward);
                }
            }
        }
        
        // Check state
        FActionData action;
        TScriptInterface<IActionInterface> actionItem;
        if (!m_Data.GetCurrentAction(action))
        {
            return;
        }
        if (!action.GetCurrentActionItem(actionItem))
        {
            return;
        }
        auto actionState = actionItem->GetState();
        switch (actionState)
        {
        case EActionState::Action_Failure:
        case EActionState::Action_Unreachable:
            m_Data.State = EExecutorState::EXECUTOR_WAITING;
            actionItem->FinishAction();
            action.Reset();

            // TODO Store data
            break;

        case EActionState::Action_Success:
        {
            actionItem->FinishAction();
            // own thing
            FThing reward;
            if (m_Data.GetCurrentReward(reward))
            {
                OwnThing(reward);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Reward of actionItem %s is lose!"), *actionItem.GetObject()->GetName());
            }

            bool switchAction = false;
            // Switch to next actionItem
            if (m_Data.IsLastActionItem())
            {
                if (m_Data.IsLastAction())
                {
                    m_Data.State = EExecutorState::EXECUTOR_FINISH;
                    m_Data.ActionIndex = 0;
                    action.Reset();
                }
                else
                {
                    // Switch to next action
                    action.Reset();
                    m_Data.SwitchAction();
                    switchAction = true;
                }
            }
            else
            {
                // Switch to next actionItem of current behvior
                action.SwitchActionItemIndex();
                switchAction = true;
            }

            // Switch to next actionItem
            if (switchAction)
            {
                FBehaviorEvent NextActionInfo;
                if (m_Data.GetActionInfo(NextActionInfo))
                {
                    if (!m_Mind->Wish->CheckThingOwned(NextActionInfo.Condition))
                    {
                        m_Data.State = EExecutorState::EXECUTOR_WAITING;
                        return;
                    }
                    FActionData nextAction;
                    if (!m_Data.GetCurrentAction(nextAction))
                    {
                        m_Data.Actions.Add(nextAction);
                    }
                    TScriptInterface<IActionInterface> nextActionItem;
                    TSubclassOf<UObject> actionClass;
                    if (m_Data.Way.GetActionClass(m_Data.ActionIndex, nextAction.ActionItemIndex, actionClass))
                    {
                        if (CreateActionItem(nextActionItem, actionClass))
                        {
                            nextActionItem->PrepareAction();
                            if (nextActionItem->IsCost())
                            {
                                // decrease thing
                                UseThing(NextActionInfo.Condition);
                            }
                        }
                        else
                        {
                            UE_LOG(LogTemp, Error, TEXT("Switch next actionItem failed, Create actionItem by class failed!"))
                        }
                    }
                    else
                    {
                        UE_LOG(LogTemp, Error, TEXT("Switch next actionItem item failed, Action index out of range!"))
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Cannot get next actionItem"))
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
        if (m_Data.GetActionInfo(behaviorInfo))
        {
            TScriptInterface<IActionInterface> actionItem;
            FActionData action;
            if (m_Data.GetCurrentAction(action))
            {
                action.GetCurrentActionItem(actionItem);
            }
            else
            {
                CreateActionItem(actionItem, behaviorInfo.ActionSequenceClasses[0]);
            }

            // Execute actionItem
            if (actionItem != nullptr)
            {
                actionItem->RunningAction();
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
        TScriptInterface<IActionInterface> actionItem;
        FActionData action;
        if (m_Data.GetCurrentAction(action))
        {
            if (action.GetCurrentActionItem(actionItem))
            {
                actionItem->FinishAction();
            }
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
                    if (GetAllSituation(condition, tempSituations, tempWay.ActionInfos[tempWay.ActionInfos.Num() - 1]))
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

bool UExecutor::GetAllSituation(FThing target, TArray<FBehaviorEvent> &situation, const FBehaviorEvent &excludeAction)
{
    situation.Empty();
    for (int i = 0; i < TotalActionInfos.Num(); ++i)
    {
        if (TotalActionInfos[i].Reward == target && TotalActionInfos[i] != excludeAction)
        {
            situation.AddUnique(TotalActionInfos[i]);
        }
    }
    return situation.Num() >= 0;
}

void UExecutor::AddSituation(TArray<FWay> &Total, TArray<FBehaviorEvent> situations, FWay preCondition)
{
    for (auto info : situations)
    {
        TArray<FBehaviorEvent> infos;
        infos.Append(preCondition.ActionInfos);
        infos.Add(info);
        Total.Add(infos);
    }
}

bool UExecutor::CreateActionItem(TScriptInterface<IActionInterface> &actionItem, TSubclassOf<UObject> actionClass)
{
    bool result = false;
    UObject *actionObj = NewObject<UObject>(this, actionClass);
    if (actionObj)
    {
        actionItem.SetInterface(dynamic_cast<IActionInterface *>(actionObj));
        actionItem.SetObject(actionObj);
        actionItem->Init(m_Mind->GetOwner());

        FActionData action;
        if (!m_Data.GetCurrentAction(action))
        {
            m_Data.Actions.Add(action);
        }
        action.AddActionItem(actionItem);
        result = true;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Executor create actionItem failed!"));
    }

    return result;
}