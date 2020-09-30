/*
    Author: baihan 
    class purpose: Interface for combat hit 
*/

#pragma once

#include "CoreMinimal.h"
#include "CombatStructure.h"
#include "HitReaction.h"
#include "HitSolution.generated.h"

UINTERFACE(Blueprintable)
class UHitSolution : public UInterface
{
    GENERATED_BODY()
};

class MELEECOMBATCORE_API IHitSolution
{
    GENERATED_BODY()

public:
    FHitSolutionInfo m_hitInfo;

public:
    // Attacking
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnHit(AActor *attackedActor);

    // init
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void InitData();

    void Init(FHitSolutionInfo data)
    {
        m_hitInfo = data;
        this->Execute_InitData(Cast<UObject>(this));
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
        if (actor->GetClass()->ImplementsInterface(UHitReaction::StaticClass()))
        {
            IHitReaction::Execute_OnHitted(actor, m_hitInfo.hurts);
            // UE_LOG(LogTemp, Warning, TEXT("Multi attack"));
        }
    }
};