// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MeleeComponents/CombatComponent.h"
#include "AttackTypeNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBATCORE_API UAttackTypeNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UCombatComponent* m_combat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hurt")
	ECombatHurt m_hurtType;
	
public:
	void BeginDestroy() override;
	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);	
};
