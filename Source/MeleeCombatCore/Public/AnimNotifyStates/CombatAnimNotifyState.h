/*
	Author: baihan 
	class purpose: animation notify for Combat
*/

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CombatComponent.h"
#include "CombatAnimNotifyState.generated.h"

/**
 *
 */
UCLASS()
class MELEECOMBATCORE_API UCombatAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UCombatComponent* m_combat;
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
