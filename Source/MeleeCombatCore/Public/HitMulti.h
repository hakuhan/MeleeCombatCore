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
    /*hit interval of multi attack*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solution")
    float m_hitInterval = 0.1f;

private:
    bool m_isCooling = false;

public:
    virtual void OnHit_Implementation(AActor *attackedActor) override;

    virtual void InitData_Implementation() override;

    virtual void OnStartDetection_Implementation() override;

    virtual void OnEndDetection_Implementation() override;
};