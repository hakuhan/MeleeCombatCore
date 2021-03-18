/*
    Author: baihan 
    Date: "2021-03-16" 
*/

#pragma once

#include "CoreMinimal.h"

#include "Core/PlanInterface.h"
#include "Core/ActionInterface.h"
#include "Plan.generated.h"

UCLASS()
class MINDCORE_API UPlan : public UObject, public IPlanInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    TArray<TScriptInterface<IActionInterface>> m_actions;

public:
    virtual void DoPlan_Implementation();
    virtual void CreatePlan_Implementation(const UThing* wish) override;
    virtual void UpdatePlan_Implementation() override;
};