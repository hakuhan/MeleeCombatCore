#include "SkillComponent/SkillEndNotify.h"

void USkillEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
    {
        return;
    }

    auto skillComponent = dynamic_cast<USkillComponent*>(MeshComp->GetOwner()->GetComponentByClass(USkillComponent::StaticClass()));
    if (skillComponent)
    {
        skillComponent->SkillEnded();
    }
}