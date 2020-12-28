#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CombatMoveInterface.h"
#include "MeleeUtils.h"
#include "Components/SkeletalMeshComponent.h"
#include "MeleeStopMoving.generated.h"

UCLASS()
class MELEECORE_API UMeleeStopMoving : public UAnimNotifyState
{
    GENERATED_BODY()
public:
    virtual void NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration);
    virtual void NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation);
    void UpdateMoveState(AActor *actor, bool canMove);
};