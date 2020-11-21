#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MeleeNotifyInterface/MeleeMoveInterface.h"
#include "MeleeUtils.h"
#include "Components/SkeletalMeshComponent.h"
#include "AnimNotifyState_CombatStopMove.generated.h"

UCLASS()
class MELEECORE_API UAnimNotifyState_CombatStopMove : public UAnimNotifyState
{
    GENERATED_BODY()
public:
    virtual void NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration);
    virtual void NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation);
    void UpdateMoveState(AActor *actor, bool canMove);
};