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
            m_Data.BehaviorIndex = 0;
            m_Data.ActionIndex = 0;
        }
    }
}

void UExecutor::ExecuteBehavior_Implementation()
{
    if (m_Data.State == EExecutorState::EXECUTOR_READY || m_Data.State == EExecutorState::EXECUTOR_EXECUTING)
    {
        // Execute current action
        FBehaviorEvent behavior;
        bool hasActon = false;
        if (m_Data.Way.GetBehavior(m_Data.BehaviorIndex, behavior))
        {
            // Get current action
            TScriptInterface<IActionInterface> action;
            if (m_Data.BehaviorIndex >= m_Data.Behaviors.Num())
            {
                hasActon = CreateAction(action, behavior.ActionSequenceClasses[m_Data.ActionIndex], m_Data.ActionIndex);
            }
            else
            {
                hasActon = true;
                action = m_Data.Behaviors[m_Data.BehaviorIndex];
            }

            // Execute action
            if (hasActon)
            {
                action->RunningAction();
            }

            // Check state
            auto actionState = action->GetState();
            switch (actionState)
            {
                case EActionState::Action_Failure:
                case EActionState::Action_Unreachable:
                    m_Data.State = EExecutorState::EXECUTOR_WAITING;
                    action->FinishAction();
                    m_Data.ActionIndex = 0;
                break;

                case EActionState::Action_Success:
                {
                    action->FinishAction();
                    // own thing
                    OnOwnThing(behavior.Reward);

                    bool switchAction = false;
                    // Switch to next action
                    if (m_Data.Way.IsLastAction(m_Data.BehaviorIndex, m_Data.ActionIndex))
                    {
                        if (m_Data.Way.IsLastBehavior(m_Data.BehaviorIndex))
                        {
                            // Check end of executor 
                            m_Data.State = EExecutorState::EXECUTOR_FINISH;
                            m_Data.BehaviorIndex = 0;
                            m_Data.ActionIndex = 0;
                        }
                        else
                        {
                            // Switch to next behavior
                            m_Data.BehaviorIndex += 1;
                            m_Data.ActionIndex = 0;
                            switchAction = true;
                        }
                    }
                    else
                    {
                        m_Data.ActionIndex += 1;
                        switchAction = true;
                    }

                    // Switch to next action
                    if (switchAction)
                    {
                        FBehaviorEvent nextBehavior;
                        if (m_Data.Way.GetBehavior(m_Data.BehaviorIndex, nextBehavior))
                        {
                            TScriptInterface<IActionInterface> nextAction;
                            TSubclassOf<UObject> actionClass;
                            if (m_Data.Way.GetActionClass(m_Data.BehaviorIndex, m_Data.ActionIndex, actionClass))
                            {
                                if (CreateAction(nextAction, actionClass, m_Data.ActionIndex))
                                {
                                    nextAction->PrepareAction();
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

                case EActionState::Action_Inactive:
                break;

            }
        }
    }
}

void UExecutor::Stop()
{
    if (m_Data.State == EExecutorState::EXECUTOR_EXECUTING)
    {
        auto action = m_Data.Behaviors[m_Data.BehaviorIndex];
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

bool UExecutor::GetAllSituation(FThing target, TArray<FBehaviorEvent> &situation, const FBehaviorEvent& excludeBehavior)
{
    situation.Empty();
    for (int i = 0; i < Behaviors.Num(); ++i)
    {
        if (Behaviors[i].Reward == target && Behaviors[i] != excludeBehavior)
        {
            situation.AddUnique(Behaviors[i]);
        }
    }
    return situation.Num() >= 0;
}

void UExecutor::AddSituation(TArray<FWay>& Total, TArray<FBehaviorEvent> situations, FWay preCondition)
{
    for (auto behavior : situations)
    {
        TArray<FBehaviorEvent> behaviors;
        behaviors.Append(preCondition.Behaviors);
        behaviors.Add(behavior);
        Total.Add(behaviors);
    }
}

bool UExecutor::CreateAction(TScriptInterface<IActionInterface>& action, TSubclassOf<UObject> actionClass, int placeActionIndex)
{
    bool result = false;
    UObject* actionObj = NewObject<UObject>(this, actionClass);
    if (actionObj)
    {
        action.SetInterface(dynamic_cast<IActionInterface*>(actionObj));
        action.SetObject(actionObj);
        action->Init(m_Mind->GetOwner());

        if (placeActionIndex >= 0)
        {
            if (m_Data.Behaviors.Num() > placeActionIndex)
            {
                m_Data.Behaviors[placeActionIndex] = action;
            }
            else
            {
                m_Data.Behaviors.Add(action);

                if (m_Data.Behaviors.Num() <= placeActionIndex)
                {
                    UE_LOG(LogTemp, Error, TEXT("Created action isn't at target index!"));
                }
            }
        }
        result = true;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Executor create action failed!"));
    }

    return result;
}