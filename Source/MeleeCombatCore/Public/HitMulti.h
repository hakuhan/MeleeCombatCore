/*
    Author: baihan 
    class purpose: Handle multi attack per animation 
*/

#pragma once

#include "CoreMinimal.h"
#include "HitSolution.h"
#include "HitMulti.generated.h"

UCLASS()
class UHitMulti : public UObject, public IHitSolution
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