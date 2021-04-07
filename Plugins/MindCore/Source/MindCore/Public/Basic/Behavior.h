/*
    Author: baihan 
    Date: "2021-03-21" 
    Class discription: Base class that achieve wishes
*/

#pragma once

#include "CoreMinimal.h"
#include "Core/BehaviorInterface.h"
#include "Core/BehaviorExecutorInterface.h"
#include "Core/MindComponentInterface.h"
#include "Structure/Thing.h"
#include "Basic/Executor.h"
#include "Structure/BehaviorEvent.h"
#include "Behavior.generated.h"

USTRUCT(BlueprintType)
struct FBehaviorItem
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Behavior)
    FThing Target;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Behavior)
    TScriptInterface<IBehaviorExecutorInterface> Executor;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Behavior)
    EBehaviorState State;
};

UCLASS(Blueprintable)
class MINDCORE_API UBehavior : public UObject, public IBehaviorInterface, public IMindComponentInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    UMind* Mind;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<UExecutor> ExecutorClass;
    UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
    TArray<FBehaviorItem> Behaviors;

public:
#pragma region behavior
    virtual void Behave_Implementation() override;
    virtual EBehaviorState GetState_Implementation() override;
#pragma endregion

#pragma region mind component
    virtual void OnInit_Implementation(UMind *mind) override
    {
        Mind = mind;
    }
    virtual void OnStop_Implementation() override;
#pragma endregion

    virtual void CreateBehavior();
    virtual void UpdateBehavior();
    virtual void ExecuteBehavior();
    virtual void ObtainThing(const FThing& thing);
    virtual void UseThing(const FThing &thing);    
};