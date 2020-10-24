#include "AnimNotify/AnimNotifyState_CombatInput.h"

void UAnimNotifyState_CombatInput::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
    {
        return;
    }

    UpdateInputState(MeshComp->GetOwner(), true);
}

void UAnimNotifyState_CombatInput::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
    {
        return;
    }

    UpdateInputState(MeshComp->GetOwner(), false);
}

void UAnimNotifyState_CombatInput::UpdateInputState(AActor *actor, bool canInput)
{
    TArray<UObject *> inputers;
    UMeleeUtils::GetImplementFromActor(actor, UMeleeInputInterface::StaticClass(), inputers);
    if (inputers.Num() > 0)
    {
        for (auto inputObj : inputers)
        {
            IMeleeInputInterface::Execute_UpdateInputState(inputObj, canInput);
        }
    }
    inputers.Empty();
}