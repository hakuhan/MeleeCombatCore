// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeleeComponents/CombatEffectComponent.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CombatEffectAnimState.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBATCORE_API UCombatEffectAnimState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UCombatEffectComponent *m_effect;

public:
	void BeginDestroy() override;
	virtual void NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation);
};
