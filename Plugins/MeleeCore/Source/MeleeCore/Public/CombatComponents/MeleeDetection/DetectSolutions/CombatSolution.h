/*
    Author: baihan 
    class purpose: Interface for melee solutoin 
*/
#pragma once
#include "MeleeCoreStructures/MeleeStructure.h"
#include "CombatReaction.h"
#include "MeleeUtils.h"
#include "CombatSolution.generated.h"

UINTERFACE(Blueprintable)
class MELEECORE_API UCombatSolution : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API ICombatSolution
{
    GENERATED_BODY()

public:
    FHurt m_HurtInfo;
    float m_HurtRate = 1;

public:
    // Attacking
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnHit(AActor *attackedActor, ECombatHitResult &outResult);

    // init
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void InitData();

    void Init(FHurt data)
    {
        UpdateHurts(data);
        this->Execute_InitData(Cast<UObject>(this));
    }

    virtual void UpdateHurts(FHurt data)
    {
        m_HurtInfo = data;
    }

    void UpdateHurtRate(float rate)
    {
        m_HurtRate = rate;
    }

    // start event
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnStartDetection();

    // end event
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnEndDetection();

protected:
    void NoticeHit(AActor *actor, ECombatHitResult &outResult)
    {
        TArray<UObject *> reacters;
        UMeleeUtils::GetImplementFromActor(actor, UCombatReaction::StaticClass(), reacters);
        if (reacters.Num() > 0)
        {
            for (auto reacter : reacters)
            {
                ICombatReaction::Execute_OnMeleeHitted(reacter, m_HurtInfo.hurts * m_HurtRate);
                outResult = ICombatReaction::Execute_GetHitResult(reacter);
            }
            // UE_LOG(LogTemp, Warning, TEXT("Multi attack"));
        }
    }
};