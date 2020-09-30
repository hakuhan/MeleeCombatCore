/*
    Author: baihan 
    class purpose: hand hit event once every animation 
*/
#pragma once

#include "CoreMinimal.h"
#include "HitSolution.h"
#include "HitOnce.generated.h"

UCLASS(Blueprintable)
class MELEECOMBATCORE_API UHitOnce : public UObject, public IHitSolution
{
    GENERATED_BODY()

private:
    TArray<AActor *> m_actors;

public:
    virtual void OnHit_Implementation(AActor *attackedActor) override;

    virtual void InitData_Implementation() override;

    virtual void OnStartDetection_Implementation() override;

    virtual void OnEndDetection_Implementation() override;
};