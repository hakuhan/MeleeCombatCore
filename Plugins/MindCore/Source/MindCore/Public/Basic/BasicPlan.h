/*
    Author: baihan 
    Date: "2021-03-16" 
*/

#pragma once

#include "CoreMinimal.h"

#include "Core/Plan.h"
#include "Core/Action.h"
#include "BasicPlan.generated.h"

UCLASS()
class MINDCORE_API UBasicPlan : public UObject, public IPlan
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    TArray<TScriptInterface<IAction>> m_actions;

public:
    virtual void CreatePlan_Implementation(const UThing* wish) override;
    virtual void UpdatePlan_Implementation() override;
};