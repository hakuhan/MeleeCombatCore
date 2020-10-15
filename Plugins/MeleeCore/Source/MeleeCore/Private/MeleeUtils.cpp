#include "MeleeUtils.h"

void UMeleeUtils::GetImplementFromActor(AActor* owner, TSubclassOf<UInterface> interface, TArray<UObject*>& array, bool checkSelf)
{
    // Check components 
    auto comp = owner->GetComponentsByInterface(interface);
    for (int i = 0; i < comp.Num(); ++i)
    {
        array.Add(comp[i]);
    }

    // Check self
    if (checkSelf && owner->GetClass()->ImplementsInterface(interface))
    {
        array.Add(owner);
    }
}