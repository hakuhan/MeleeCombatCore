#include "Basic/Executor.h"

void UExecutor::CreateBehavior_Implementation()
{
    // Create action chain
    bool isWayOk = FindWay(m_Data.Target, m_Data.Ways);

    if (!isWayOk)
    {
        m_Data.State = EExecutorState::EXECUTOR_WAITING;
    }
    else
    {
        m_Data.State = EExecutorState::EXECUTOR_READY;
    }
    
}

void UExecutor::UpdateBehavior_Implementation()
{
    // Checkout road
    if (m_Data.State == EExecutorState::EXECUTOR_WAITING)
    {
        bool isWayOk = FindWay(m_Data.Target, m_Data.Ways);
        if (isWayOk)
        {
            m_Data.State = EExecutorState::EXECUTOR_READY;
        }
    }
}

void UExecutor::ExecuteBehavior_Implementation()
{
    // Execute current action or executor
    if (m_Data.State == EExecutorState::EXECUTOR_READY || m_Data.State == EExecutorState::EXECUTOR_EXECUTING)
    {

    }
}

void UExecutor::Stop()
{
    
}

EExecutorState UExecutor::GetExecuteState_Implementation()
{
    return EExecutorState::EXECUTOR_READY;
}

bool UExecutor::FindWay_Implementation(FThing target, TArray<FBehaviorEvent>& ways)
{
    bool findWays = false;
    bool noWay = false;
    ways.Empty();

    FThing& condition = target;
    TArray<FBehaviorEvent> failedStartupBehaviors = {};
    TArray<FBehaviorEvent> tempWays;
    while (findWays || noWay)
    {
        // TODO
        // Find owned
        bool isOwned = m_Mind->Wish->CheckThingOwned(condition);

        // Find got ways
        int priority = -1; 
        int behaviorIndex = -1;
        for (int i = 0; i < Behaviors.Num(); ++i)
        {
            if (Behaviors[i].Reward.Name == condition.Name 
                && Behaviors[i].Reward.Priority > priority
                && !failedStartupBehaviors.Contains(Behaviors[i]))
            {
                behaviorIndex = i;
                priority = Behaviors[i].Reward.Priority;
            }
        }

        if (behaviorIndex >= 0)
        {
            tempWays.Add(Behaviors[behaviorIndex]);
            condition = Behaviors[behaviorIndex].Condition;
        }
        else
        {
            if (condition == target)
            {
                noWay = true;
            }
            else
            {
                auto failedBehavior = tempWays.Pop();
                failedStartupBehaviors.Add(failedBehavior);
            }
        }

        if (condition == FThing::EmptyThing())
        {
            findWays = true;
            ways.Append(tempWays);
        }
        else if (failedStartupBehaviors.Num() == Behaviors.Num())
        {
            noWay = true;
        }
    }

    return findWays;
}