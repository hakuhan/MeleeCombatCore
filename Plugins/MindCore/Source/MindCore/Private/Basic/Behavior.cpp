#include "Basic/Behavior.h"

// TODO implement
void UBehavior::Behave_Implementation()
{
    CreateBehavior();

    UpdateBehavior();

    ExecuteBehavior();
}

EBehaviorState UBehavior::GetState_Implementation()
{
    return EBehaviorState::BEHAVIOR_READY;
}

void UBehavior::OnStop_Implementation()
{
    for (int i = 0; i < Behaviors.Num(); ++i)
    {
        UExecutor *executor = dynamic_cast<UExecutor *>(Behaviors[i].Executor.GetObject());
        if (executor)
        {
            executor->Stop();
        }
    }
}

void UBehavior::CreateBehavior()
{
    // Get wishes
    TArray<FThing> Wishes;
    Mind->Wish->GetWishes(Wishes);

    // Find Executor to execute
    for (int i = 0; i < Wishes.Num(); ++i)
    {
        int behaviorIndex = Behaviors.IndexOfByPredicate([&](const FBehaviorItem &Item) { return Item.Target.Name == Wishes[i].Name; });
        if (behaviorIndex < 0)
        {
            // Create executor and run
            UExecutor *executor = NewObject<UExecutor>(this, ExecutorClass);
            if (executor == nullptr)
            {
                UE_LOG(LogTemp, Error, TEXT("Exector cannot be instanced!"))
            }
            else
            {
                executor->Init(Wishes[i], Mind);
                executor->OnObtainThings.BindUObject(this, &UBehavior::ObtainThing);

                IBehaviorExecutorInterface::Execute_CreateBehavior(executor);
                FBehaviorItem item;
                item.Target = Wishes[i];
                item.Executor.SetInterface(dynamic_cast<IBehaviorExecutorInterface *>(executor));
                item.Executor.SetObject(executor);
                item.State = EBehaviorState::BEHAVIOR_READY;
                Behaviors.Add(item);
            }
        }
        else
        {
            // Update executor
            Behaviors[behaviorIndex].Executor->UpdateBehavior();
        }
    }
}

void UBehavior::UpdateBehavior()
{
    for (int j = 0; j < Behaviors.Num(); ++j)
    {
        auto state = Behaviors[j].Executor->GetExecuteState();

        if (state == EExecutorState::EXECUTOR_FINISH)
        {
            // Remember
            TScriptInterface<IRememberInterface> remember;
            Mind->GetRemember(remember);
            FMemoryFragment memory;
            remember->Remind(Behaviors[j].Target.Name, memory);
            memory.Target = Behaviors[j].Target;

            memory.Type = EMemoryType::Memory_Insensible;
            // TODO remember executor chain

            remember->Remember(memory);

            // Update wish
            Mind->Wish->ObtainThing(Behaviors[j].Target);

        }
    }
}

void UBehavior::ExecuteBehavior()
{
    if (Behaviors.Num() <= 0)
    {
        return;
    }

    // Find Target Behavior
    int priority = 0;
    int targetIndex = 0;
    for (int i = 0; i < Behaviors.Num(); ++i)
    {
        if (priority < Behaviors[i].Target.Priority)
        {
            auto state = Behaviors[i].Executor->GetExecuteState();
            if (state == EExecutorState::EXECUTOR_READY || state == EExecutorState::EXECUTOR_EXECUTING)
            {
                targetIndex = i;
                priority = Behaviors[i].Target.Priority;
            }
        }
    }

    // Execute
    Behaviors[targetIndex].Executor->ExecuteBehavior();
}

void UBehavior::ObtainThing(const FThing &thing)
{
    Mind->Wish->ObtainThing(thing);
}