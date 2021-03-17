/*
    Author: baihan 
    Date: "2021-03-16" 
    Class discription: Base action implements IAction 
*/

#pragma once

#include "CoreMinimal.h"
#include "Core/Action.h"
#include "Structure/ActionInfo.h"
#include "BasicAction.generated.h"

UCLASS()
class MINDCORE_API UBasicAction : public UObject, public IAction
{
    GENERATED_BODY()
public:
    UActionInfo* m_Info;

    virtual void PrepareAction_Implementation();
    virtual void RunningAction_implementation();
    virtual void FinishAction_Implementation();

    void Init(UActionInfo* info);
};