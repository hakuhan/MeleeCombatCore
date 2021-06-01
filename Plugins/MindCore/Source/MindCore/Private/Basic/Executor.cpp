#include "Basic/Executor.h"

void UExecutor::CreateBehavior_Implementation()
{
    // Create actionSequence chain
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
    // Check way
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
        // Check action validaty
        for (auto validaty : m_Data.Validaties)
        {
            if (!IActionValidatyInterface::Execute_CheckActionValidaty(validaty.GetObject(), m_Mind->GetOwner()))
            {
                m_Data.State = EExecutorState::EXECUTOR_WAITING;
                return;
            }
        }

        // Check thing lose
        for (int i = 0; i < m_Data.Actions.Num(); ++i)
        {
            FThing reward;
            for (int j = 0; j < m_Data.Actions[i].ActionSequence.Num(); ++j)
            {
                auto actionSequence = m_Data.Actions[i].ActionSequence[j];
                if (actionSequence->Execute_GetState(actionSequence.GetObject()) == EActionState::Action_Success 
                    && CheckPreconditions(m_Data.Way.ActionInfos[0].RewardTable, reward) 
                    && actionSequence->Execute_CanEfficacyLose(actionSequence.GetObject()) 
                    && actionSequence->Execute_CheckLose(actionSequence.GetObject()))
                {
                    UseThing(reward);
                    actionSequence->Execute_OnLose(actionSequence.GetObject());
                    m_Data.State = EExecutorState::EXECUTOR_WAITING;
                }
            }
        }

        FActionData action;
        TScriptInterface<IActionInterface> actionSequence;
        if (!m_Data.GetCurrentAction(action, false))
        {
            UE_LOG(LogTemp, Error, TEXT("Current Action lost!"))
            return;
        }
        if (!action.GetCurrentActionSequence(actionSequence))
        {
            UE_LOG(LogTemp, Error, TEXT("Current Action item lost!"))
            return;
        }
        // Check state
        auto actionState = IActionInterface::Execute_GetState(actionSequence.GetObject());
        switch (actionState)
        {
        case EActionState::Action_Failure:
        case EActionState::Action_Unreachable:
            m_Data.State = EExecutorState::EXECUTOR_WAITING;
            IActionInterface::Execute_FinishAction(actionSequence.GetObject());
            action.Reset();

            // TODO Store data
            break;

        case EActionState::Action_Success:
        {
            IActionInterface::Execute_FinishAction(actionSequence.GetObject());

            // Check behaviors
            bool switchAction = false;
            if (m_Data.IsLastActionSequence())
            {
                if (m_Data.IsLastAction())
                {
                    m_Data.State = EExecutorState::EXECUTOR_FINISH;
                    m_Data.ActionIndex = 0;
                    action.Reset();
                    m_Data.Actions.Empty();
                }
                else
                {
                    OwnCurrentTarget();

                    // Switch to next action
                    action.Reset();
                    m_Data.SwitchAction();
                    switchAction = true;
                }
            }
            else
            {
                OwnCurrentTarget();

                // Switch to next actionSequence of current behavior
                action.GainActionSequenceIndex();
                switchAction = true;
            }

            // Switch to next actionSequence
            if (switchAction)
            {
                FActionInfo NextActionInfo;
                FThing nextCondition;
                if (m_Data.GetActionInfo(NextActionInfo))
                {
                    if (!CheckPreconditions(NextActionInfo.PreconditionTable, nextCondition))
                    {
                        m_Data.State = EExecutorState::EXECUTOR_WAITING;
                        return;
                    }
                    FActionData nextAction;
                    if (m_Data.GetCurrentAction(nextAction))
                    {
                        TScriptInterface<IActionInterface> nextSequence;
                        TSubclassOf<UObject> actionClass;
                        if (m_Data.Way.GetActionClass(m_Data.ActionIndex, nextAction.ActionSequenceIndex, actionClass))
                        {
                            if (nextAction.GetCurrentActionSequence(nextSequence) || CreateActionSequence(nextSequence, actionClass))
                            {
                                BeginSequence(nextSequence, nextCondition);
                            }
                            else
                            {
                                UE_LOG(LogTemp, Error, TEXT("Switch next actionSequence failed, Create actionSequence by class failed!"))
                            }
                        }
                        else
                        {
                            UE_LOG(LogTemp, Error, TEXT("Switch next actionSequence item failed, Action index out of range!"))
                        }
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Cannot get next actionSequence"))
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
        FActionInfo behaviorInfo;
        if (m_Data.GetActionInfo(behaviorInfo))
        {
            TScriptInterface<IActionInterface> actionSequence;
            FActionData action;
            if (m_Data.GetCurrentAction(action, false))
            {
                if (!action.GetCurrentActionSequence(actionSequence))
                {
                    CreateActionSequence(actionSequence, behaviorInfo.ActionSequenceClasses[action.ActionSequenceIndex]);
                    FThing precondition;
                    CheckPreconditions(behaviorInfo.PreconditionTable, precondition);
                    BeginSequence(actionSequence, precondition);
                }
            }
            else
            {
                CreateActionSequence(actionSequence, behaviorInfo.ActionSequenceClasses[0]);
                FThing precondition;
                CheckPreconditions(behaviorInfo.PreconditionTable, precondition);
                BeginSequence(actionSequence, precondition);
            }

            // Execute actionSequence
            if (actionSequence.GetObject() != nullptr)
            {
                actionSequence->Execute_RunningAction(actionSequence.GetObject());
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
        TScriptInterface<IActionInterface> actionSequence;
        FActionData action;
        if (m_Data.GetCurrentAction(action, false))
        {
            if (action.GetCurrentActionSequence(actionSequence))
            {
                actionSequence->Execute_FinishAction(actionSequence.GetObject());
            }
        }
    }
}

EExecutorState UExecutor::GetExecuteState_Implementation()
{
    return m_Data.State;
}

void UExecutor::UpdateState_Implementation(EExecutorState state)
{
    m_Data.State = state;
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

        UpdateValidaties(way);
        return true;
    }

    return false;
}

bool UExecutor::GetAllWays(FThing target, TArray<FWay> &ways)
{
    ways.Empty();
    bool gotAllWays = false;
    TArray<FWay> CheckingWays;
    TArray<FActionInfo> solutions;
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
                    TArray<FActionInfo> tempSituations;
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

bool UExecutor::GetAllSolutions(const FDataTableRows &goals, const FActionInfo &excludeAction, TArray<FActionInfo> &outSolution)
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

bool UExecutor::GetAllSolutionsByThing(const FThing &goal, TArray<FActionInfo> &outSolutions)
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

void UExecutor::StashWay(TArray<FWay> &Ways, TArray<FActionInfo> situations, FWay originalGoals)
{
    for (auto item : situations)
    {
        TArray<FActionInfo> wayInfos;
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

bool UExecutor::CreateActionSequence(TScriptInterface<IActionInterface> &actionSequence, TSubclassOf<UObject> actionClass)
{
    bool result = false;
    UObject *actionObj = NewObject<UObject>(this, actionClass);
    if (actionObj)
    {
        actionSequence.SetInterface(dynamic_cast<IActionInterface *>(actionObj));
        actionSequence.SetObject(actionObj);
        actionSequence->Execute_Init(actionObj, m_Mind->GetOwner());
        UMindAction* sequence = dynamic_cast<UMindAction*>(actionObj);
        if (sequence)
        {
            sequence->OnUpdateDifficulty.BindUObject(this,  &UExecutor::UpdateDifficulty);
        }

        FActionData action;
        if (m_Data.GetCurrentAction(action))
        {
            action.AddSequence(actionSequence);
            m_Data.UpdateCurrentAction(action);
            result = true;
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Executor create actionSequence failed!"));
    }

    return result;
}

bool UExecutor::BeginSequence(TScriptInterface<IActionInterface>& sequence, const FThing& precondition)
{
    if (sequence.GetObject())
    {
        sequence->Execute_PrepareAction(sequence.GetObject());
        if (sequence->Execute_IsCost(sequence.GetObject()))
        {
            // decrease thing
            UseThing(precondition);
        }

        return true;
    }

    return false;
}

void UExecutor::UpdateDifficulty(UMindAction* targetAction, EActionDifficulty difficulty)
{
    // Find target action
    FActionInfo* targetInfo = nullptr;
    for (FActionData actionData : m_Data.Actions)
    {
        int targetIndex = actionData.ActionSequence.IndexOfByPredicate([&](const TScriptInterface<IActionInterface>& sequence){
            return sequence.GetObject() == targetAction;
        });
        if (targetIndex >= 0)
        {
            targetInfo = &m_Data.Way.ActionInfos[targetIndex];
            break;
        }
    }

    // Update difficulty
    if (targetInfo)
    {
        for (int i = 0; i < TotalActions.Num(); ++i)
        {
            if (TotalActions[i] == *targetInfo)
            {
                TotalActions[i].Difficulty = difficulty;
            }
        }
    }
}

void UExecutor::OwnCurrentTarget()
{
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
        UE_LOG(LogTemp, Warning, TEXT("Reward is lost!"));
    }
}

void UExecutor::UpdateValidaties(const FWay& way)
{
    m_Data.Validaties.Empty();

    for (int i = 0; i < way.ActionInfos.Num(); ++i)
    {
        if (way.ActionInfos[i].ActionValidatyClass.Get() != nullptr)
        {
            TScriptInterface<IActionValidatyInterface> validaty;
            UObject* validatyObj = NewObject<UObject>(this, way.ActionInfos[i].ActionValidatyClass);
            validaty.SetInterface(dynamic_cast<IActionValidatyInterface*>(validatyObj));
            validaty.SetObject(validatyObj);
            m_Data.Validaties.Add(validaty);
        }
    }
}
