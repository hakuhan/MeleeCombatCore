#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CombatMoveInterface.h"
#include "MeleeUtils.h"
#include "Components/SkeletalMeshComponent.h"
#include "MeleeStopMovingNotify.generated.h"

UCLASS()
class MELEECORE_API UMeleeStopMovingNotify : public UAnimNotifyState
{
    GENERATED_BODY()
public:
    virtual void NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration);
    virtual void NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation);
    void UpdateMoveState(AActor *actor, bool canMove);
};