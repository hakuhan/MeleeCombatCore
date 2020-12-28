/*
    Author: baihan 
    class purpose: Handle multi attack per animation 
*/

#pragma once

#include "CoreMinimal.h"
#include "MeleeSolution.h"
#include "TimerManager.h"
#include "Actor_Countdown.h"
#include "MeleeSolution_Multi.generated.h"

UCLASS()
class UMeleeSolution_Multi : public UObject, public IMeleeSolution
{
    GENERATED_BODY()

private:
    TArray<AActor *> m_Actors;

public:
    ~UMeleeSolution_Multi();
    /*hit interval of multi attack*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solution")
    float m_MeleeInterval = 0.1f;

private:
    UPROPERTY()
    TMap<AActor*, FTimerHandle> m_IntervalTimers;

public:
    virtual void OnHit_Implementation(AActor *attackedActor, ECombatHitResult &outResult) override;

    virtual void InitData_Implementation() override;

    virtual void OnStartDetection_Implementation() override;

    virtual void OnEndDetection_Implementation() override;

    virtual void UpdateHurts(FHurt data) override;

    UFUNCTION(BlueprintCallable)
    bool IsCooling(AActor* hittedActor);

protected:
    void CoolOver();
};