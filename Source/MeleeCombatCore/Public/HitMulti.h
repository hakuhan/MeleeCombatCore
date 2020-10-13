/*
    Author: baihan 
    class purpose: Handle multi attack per animation 
*/

#pragma once

#include "CoreMinimal.h"
#include "HitSolution.h"
#include "TimerManager.h"
#include "HitMulti.generated.h"

UCLASS()
class UHitMulti : public UObject, public IHitSolution
{
    GENERATED_BODY()

private:
    TArray<AActor *> m_actors;
    // TArray<float> m_intervals;

public:
    ~UHitMulti();
    /*hit interval of multi attack*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solution")
    float m_hitInterval = 0.1f;

private:
    UPROPERTY()
    TMap<AActor*, FTimerHandle> m_intervalTimers;

public:
    virtual void OnHit_Implementation(AActor *attackedActor) override;

    virtual void InitData_Implementation() override;

    virtual void OnStartDetection_Implementation() override;

    virtual void OnEndDetection_Implementation() override;

    UFUNCTION(BlueprintCallable)
    bool IsCooling(AActor* hittedActor);

protected:
    void CoolOver();
};