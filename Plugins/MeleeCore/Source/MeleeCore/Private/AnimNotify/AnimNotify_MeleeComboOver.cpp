// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_MeleeComboOver.h"

void UAnimNotify_MeleeComboOver::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
    {
        return;
    }

    TArray<UObject *> _comboObjs;
    UMeleeUtils::GetImplementFromActor(MeshComp->GetOwner(), UComboInterface::StaticClass(), _comboObjs);
    if (_comboObjs.Num() > 0)
    {
        for (auto _comboObj : _comboObjs)
        {
            IComboInterface::Execute_OnComboOver(_comboObj);
        }
    }
}
