/*
    Author: baihan 
    class purpose: Interface for combat hit 
*/

#pragma once

#include "CoreMinimal.h"
#include "CombatStructure.h"
#include "HitReaction.h"
#include "MeleeUtils.h"
#include "HitSolution.generated.h"

UINTERFACE(Blueprintable)
class MELEECOMBATCORE_API UHitSolution : public UInterface
{
    GENERATED_BODY()
};

class MELEECOMBATCORE_API IHitSolution
{
    GENERATED_BODY()

public:
    FHurt m_HurtInfo;
    float m_hurtRate = 1;

public:
    // Attacking
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnHit(AActor *attackedActor);

    // init
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void InitData();

    void Init(FHurt data)
    {
        UpdateHurts(data);
        this->Execute_InitData(Cast<UObject>(this));
    }

    void UpdateHurts(FHurt data)
    {
        m_HurtInfo = data;
    }

    void UpdateHurtRate(float rate)
    {
        m_hurtRate = rate;
    }

    // start event
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnStartDetection();

    // end event
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnEndDetection();

protected:
    void NoticeHit(AActor *actor)
    {
        TArray<UObject *> reacters;
        UMeleeUtils::GetImplementFromActor(actor, UHitReaction::StaticClass(), reacters);
        if (reacters.Num() > 0)
        {
            for (auto reacter : reacters)
            {
                IHitReaction::Execute_OnHitted(reacter, m_HurtInfo.hurts * m_hurtRate);
            }
            // UE_LOG(LogTemp, Warning, TEXT("Multi attack"));
        }
    }
};