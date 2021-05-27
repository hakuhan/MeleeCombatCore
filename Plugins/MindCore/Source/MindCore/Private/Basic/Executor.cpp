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
            FThing reward;
            for (int j = 0; j < m_Data.Actions[i].Items.Num(); ++j)
            {
                auto actionItem = m_Data.Actions[i].Items[j];
                if (actionItem->Execute_GetState(actionItem.GetObject()) == EActionState::Action_Success 
                    && CheckPreconditions(m_Data.Way.ActionInfos[0].Reward, reward) 
                    && actionItem->Execute_CanEfficacyLose(actionItem.GetObject()) 
                    && actionItem->Execute_CheckLose(actionItem.GetObject()))
                {
                    UseThing(reward);
                    actionItem->Execute_OnLose(actionItem.GetObject());
                }
            }
        }

        // Check state
        FActionData action;
        TScriptInterface<IActionInterface> actionItem;
        if (!m_Data.GetCurrentAction(action, false))
        {
            UE_LOG(LogTemp, Error, TEXT("Current Action lost!"))
            return;
        }
        if (!action.GetCurrentActionItem(actionItem))
        {
            UE_LOG(LogTemp, Error, TEXT("Current Action item lost!"))
            return;
        }
        auto actionState = IActionInterface::Execute_GetState(actionItem.GetObject());
        switch (actionState)
        {
        case EActionState::Action_Failure:
        case EActionState::Action_Unreachable:
            m_Data.State = EExecutorState::EXECUTOR_WAITING;
            IActionInterface::Execute_FinishAction(actionItem.GetObject());
            action.Reset();

            // TODO Store data
            break;

        case EActionState::Action_Success:
        {
            IActionInterface::Execute_FinishAction(actionItem.GetObject());
            // own thing
            TArray<FThing *> reward;
            if (m_Data.GetCurrentReward(reward))
            {
                for (int i = 0; i < reward.Num(); ++i)
                {
                    if (reward[i])
                        OwnThing(*reward[i]);
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Reward of actionItem %s is lost!"), *actionItem.GetObject()->GetName());
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
                FExecutorItem NextActionInfo;
                FThing nextCondition;
                if (m_Data.GetActionInfo(NextActionInfo))
                {
                    if (!CheckPreconditions(NextActionInfo.precondition, nextCondition))
                    {
                        m_Data.State = EExecutorState::EXECUTOR_WAITING;
                        return;
                    }
                    FActionData nextAction;
                    if (m_Data.GetCurrentAction(nextAction))
                    {
                        TScriptInterface<IActionInterface> nextActionItem;
                        TSubclassOf<UObject> actionClass;
                        if (m_Data.Way.GetActionClass(m_Data.ActionIndex, nextAction.ActionItemIndex, actionClass))
                        {
                            if (CreateActionItem(nextActionItem, actionClass))
                            {
                                nextActionItem->Execute_PrepareAction(nextActionItem.GetObject());
                                if (nextActionItem->Execute_IsCost(nextActionItem.GetObject()))
                                {
                                    // decrease thing
                                    UseThing(nextCondition);
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
        FExecutorItem behaviorInfo;
        if (m_Data.GetActionInfo(behaviorInfo))
        {
            TScriptInterface<IActionInterface> actionItem;
            FActionData action;
            if (m_Data.GetCurrentAction(action, false))
            {
                if (!action.GetCurrentActionItem(actionItem))
                {
                    CreateActionItem(actionItem, behaviorInfo.ActionSequenceClasses[action.ActionItemIndex]);
                }
            }
            else
            {
                CreateActionItem(actionItem, behaviorInfo.ActionSequenceClasses[0]);
            }

            // Execute actionItem
            if (actionItem.GetObject() != nullptr)
            {
                actionItem->Execute_RunningAction(actionItem.GetObject());
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
        if (m_Data.GetCurrentAction(action, false))
        {
            if (action.GetCurrentActionItem(actionItem))
            {
                actionItem->Execute_FinishAction(actionItem.GetObject());
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
    TArray<FWay> CheckingWays;
    TArray<FExecutorItem> solutions;
    if (GetAllSolutionsByThing(target, solutions))
    {
        // Get all solution of main target
        StashWay(CheckingWays, solutions);

        // Find situations of children
        while (!gotAllWays)
        {
            if (CheckingWays.Num() > 0)
            {
                // Check and remove solution one by one
                auto tempWay = CheckingWays.Pop();

                FDataTableRows tempCondition;
                if (tempWay.HasPrecondition(tempCondition))
                {
                    TArray<FExecutorItem> tempSituations;
                    if (GetAllSolutions(tempCondition, tempWay.ActionInfos[tempWay.ActionInfos.Num() - 1], tempSituations))
                    {
                        StashWay(CheckingWays, tempSituations, tempWay);
                    }
                    else
                    {
                        tempWay.Reverse();
                        ways.Add(tempWay);
                    }
                }
                else
                {
					tempWay.Reverse();
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

bool UExecutor::GetAllSolutions(const FDataTableRows &goals, const FExecutorItem &excludeAction, TArray<FExecutorItem> &outSolution)
{
    outSolution.Empty();
    for (int i = 0; i < TotalActions.Num(); ++i)
    {
        if (TotalActions[i].IsNeedsMatched(goals) && TotalActions[i] != excludeAction)
        {
            outSolution.AddUnique(TotalActions[i]);
        }
    }
    return outSolution.Num() >= 0;
}

bool UExecutor::GetAllSolutionsByThing(const FThing &goal, TArray<FExecutorItem> &outSolutions)
{
    outSolutions.Empty();
    for (int i = 0; i < TotalActions.Num(); ++i)
    {
        if (TotalActions[i].IsNeedsMatched(*goal.Name))
        {
            outSolutions.AddUnique(TotalActions[i]);
        }
    }
    return outSolutions.Num() >= 0;
}

void UExecutor::StashWay(TArray<FWay> &Ways, TArray<FExecutorItem> situations, FWay originalGoals)
{
    for (auto item : situations)
    {
        TArray<FExecutorItem> wayInfos;
        wayInfos.Append(originalGoals.ActionInfos);
        wayInfos.Add(item);
        Ways.Add(wayInfos);
    }
}

bool UExecutor::CheckPreconditions(const FDataTableRows &precondition, FThing &outTarget)
{
    TArray<FThing *> conditions;
    precondition.GetRows(TEXT("Get preconditions"), conditions);
    for (int i = 0; i < conditions.Num(); ++i)
    {
        if (conditions[i] && m_Mind->Wish->Execute_CheckThingOwned(m_Mind->Wish.GetObject(), *conditions[i]))
        {
            outTarget = *conditions[i];
            return true;
        }
    }

    return false;
}

bool UExecutor::CreateActionItem(TScriptInterface<IActionInterface> &actionItem, TSubclassOf<UObject> actionClass)
{
    bool result = false;
    UObject *actionObj = NewObject<UObject>(this, actionClass);
    if (actionObj)
    {
        actionItem.SetInterface(dynamic_cast<IActionInterface *>(actionObj));
        actionItem.SetObject(actionObj);
        actionItem->Execute_Init(actionObj, m_Mind->GetOwner());

        FActionData action;
        if (m_Data.GetCurrentAction(action))
        {
            action.AddActionItem(actionItem);
            m_Data.Actions.Add(action);
            m_Data.UpdateCurrentAction(action);
            result = true;
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Executor create actionItem failed!"));
    }

    return result;
}