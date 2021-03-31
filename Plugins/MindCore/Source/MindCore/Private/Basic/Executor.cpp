#include "Basic/Executor.h"

void UExecutor::CreateBehavior_Implementation()
{
    // Create action chain
}

void UExecutor::UpdateBehavior_Implementation()
{
    // Checkout road
}

void UExecutor::ExecuteBehavior_Implementation()
{
    // Execute current action or executor
}

void UExecutor::Stop()
{
    
}

EExecutorState UExecutor::GetExecuteState_Implementation()
{
    return EExecutorState::EXECUTOR_READY;
}