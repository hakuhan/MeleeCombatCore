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

void UBehavior::CreateBehavior()
{
    // Get wishes
    TArray<FThing> Wishes;
    IWishInterface::Execute_GetWishes(Mind->Wish.GetObject(), Wishes);

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
                executor->OnObtainThing.BindUObject(this, &UBehavior::ObtainThing);
                executor->OnUseThing.BindUObject(this, &UBehavior::UseThing);

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
            IBehaviorExecutorInterface::Execute_UpdateBehavior(Behaviors[behaviorIndex].Executor.GetObject());
        }
    }
}

void UBehavior::UpdateBehavior()
{
    for (int j = 0; j < Behaviors.Num(); ++j)
    {
        auto state = IBehaviorExecutorInterface::Execute_GetExecuteState(Behaviors[j].Executor.GetObject());

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

            // TODO Clean executor datas

            remember->Remember(memory);

            // Update wish
            IWishInterface::Execute_ObtainThing(Mind->Wish.GetObject(), Behaviors[j].Target);

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
    int priority = -1;
    int targetIndex = 0;
    for (int i = 0; i < Behaviors.Num(); ++i)
    {
        if (priority < Behaviors[i].Target.Priority)
        {
            auto state = IBehaviorExecutorInterface::Execute_GetExecuteState(Behaviors[i].Executor.GetObject());
            if (state == EExecutorState::EXECUTOR_READY || state == EExecutorState::EXECUTOR_EXECUTING)
            {
                targetIndex = i;
                priority = Behaviors[i].Target.Priority;
            }
        }
    }

    // Execute
    IBehaviorExecutorInterface::Execute_ExecuteBehavior(Behaviors[targetIndex].Executor.GetObject());
}

void UBehavior::ObtainThing(const FThing &thing)
{
    Mind->Wish->ObtainThing(thing);
}

void UBehavior::UseThing(const FThing &thing)
{
    Mind->Wish->LoseThing(thing);
}