/*
    Author: baihan 
    Date: "2021-03-21" 
    Class discription: This is controlling a sequence of action that to get wishes 
*/

#pragma once

#include "CoreMinimal.h"
#include "Basic/Executor.h"
#include "OrderExecutor.generated.h"

UCLASS(Blueprintable)
class MINDCORE_API UOrderExecutor : public UExecutor
{
    GENERATED_BODY()
public:
    virtual void CreateBehavior_Implementation() override;
    virtual void UpdateBehavior_Implementation() override;
    virtual void ExecuteBehavior_Implementation() override;
    virtual void GetExecuteState_Implementation() override;
};

