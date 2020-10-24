#include "MeleeUtils.h"

void UMeleeUtils::GetImplementFromActor(AActor *owner, TSubclassOf<UInterface> interface, TArray<UObject *> &array, bool checkSelf)
{
    if (owner == nullptr)
    {
        return;
    }

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

// template <typename InterfaceType>
// void UMeleeUtils::CallInterfaceFromActor(AActor *actor, TScriptInterface<InterfaceType> interface, UMeleeUtils::FCallInterfaceDelegate function , bool value)
// {
//     TArray<UObject *> inputers;
//     // UMeleeUtils::GetImplementFromActor(actor, (*(InterfaceType *)interface.GetInterface())::UClassType::StaticClass(), inputers);
//     UMeleeUtils::GetImplementFromActor(actor, interface, inputers);
//     if (inputers.Num() > 0)
//     {
//         for (auto inputObj : inputers)
//         {
//             function(inputObj, params);
//         }
//     }
//     inputers.Empty();
// }