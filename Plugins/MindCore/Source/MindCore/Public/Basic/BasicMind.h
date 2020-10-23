/*
    Author: baihan 
    class purpose: Basic mind which provide baisc AI
*/

#pragma once

#include "Components/ActorComponent.h"

#include "Core/Mind.h"
#include "Core/Wish.h"
#include "Core/Plan.h"
#include "Core/Superintend.h"
#include "Core/Action.h"
#include "Core/Imagine.h"
#include "Core/Remember.h"

#include "BasicMind.generated.h"

UCLASS(ClassGroup = (Mind), meta = (BlueprintSpawnableComponent))
class MINDCORE_API UBasicMind : public UActorComponent, public IMind
{
    GENERATED_BODY()

public:
    void BeginPlay() override;
    void BeginDestroy() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
    UPROPERTY()
    TScriptInterface<IWish> m_wish;
    UPROPERTY()
    TScriptInterface<IPlan> m_plan;
    UPROPERTY()
    TScriptInterface<ISuperintend> m_superintend;
    UPROPERTY()
    TArray<TScriptInterface<IAction>> m_actions;
    UPROPERTY()
    TScriptInterface<IRemember> m_remember;
    UPROPERTY()
    TScriptInterface<IImagine> m_imagine;
};