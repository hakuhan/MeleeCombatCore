/*
    Author: baihan 
    class purpose: Notice input range 
*/

#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MeleeNotifyInterface/MeleeInputInterface.h"
#include "MeleeUtils.h"
#include "AnimNotifyState_CombatInput.generated.h"

UCLASS()
class MELEECORE_API UAnimNotifyState_CombatInput : public UAnimNotifyState
{
    GENERATED_BODY()

public:

    virtual void NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration);
	virtual void NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation);
    void UpdateInputState(AActor *actor, bool canInput);
};