#include "AnimNotify/AnimNotifyState_CombatStopMove.h"

void UAnimNotifyState_CombatStopMove::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
    {
        return;
    }

    UpdateMoveState(MeshComp->GetOwner(), false);
}

void UAnimNotifyState_CombatStopMove::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
    {
        return;
    }

    UpdateMoveState(MeshComp->GetOwner(), true);
}

void UAnimNotifyState_CombatStopMove::UpdateMoveState(AActor *actor, bool canMove)
{
    TArray<UObject *> _moveOjbs;
    UMeleeUtils::GetImplementFromActor(actor, UMeleeMoveInterface::StaticClass(), _moveOjbs);
    if (_moveOjbs.Num() > 0)
    {
        for (auto inputObj : _moveOjbs)
        {
            IMeleeMoveInterface::Execute_UpdateMoveState(inputObj, canMove);
        }
    }
    _moveOjbs.Empty();
}