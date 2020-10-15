/*
    Author: baihan 
    class purpose: Interface for melee solutoin 
*/
#pragma once
#include "MeleeCoreStructures/MeleeStructure.h"
#include "MeleeReaction.h"
#include "MeleeUtils.h"
#include "MeleeSolution.generated.h"

UINTERFACE(Blueprintable)
class MELEECORE_API UMeleeSolution : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API IMeleeSolution
{
    GENERATED_BODY()

public:
    FHurt m_HurtInfo;
    float m_HurtRate = 1;

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
        m_HurtRate = rate;
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
        UMeleeUtils::GetImplementFromActor(actor, UMeleeReaction::StaticClass(), reacters);
        if (reacters.Num() > 0)
        {
            for (auto reacter : reacters)
            {
                IMeleeReaction::Execute_OnMeleeHitted(reacter, m_HurtInfo.hurts * m_HurtRate);
            }
            // UE_LOG(LogTemp, Warning, TEXT("Multi attack"));
        }
    }
};