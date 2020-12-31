#include "MeleeUtils.h"
#include "MeleeDetection/DetectMelee.h"

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

bool UMeleeUtils::EnableWeaponByType(UDetectMelee *detectMelee, UPARAM(meta=(Bitmask, BitmaskEnum=EAttackWeapon)) uint8 WeaponType, bool enable, bool refreshWeapons)
{
    bool result = false;

    if (detectMelee == nullptr || detectMelee->GetOwner() == nullptr)
    {
        UE_LOG(LogTemp, Warning,TEXT("Delect component or actor does not valid!"));
        return result;
    }

    if (refreshWeapons)
    {
        detectMelee->UpdateWeapon();
    }

    // Change weapon state
    TArray<TScriptInterface<IMeleeWeapon>> weapons;
    detectMelee->GetWeapons(weapons);
    for (auto w : weapons)
    {
        if (w && w->IsTargetWeapon(WeaponType))
        {
            w->SetWeaponEnabled(enable);
            result = true;
        }
    }

    return result;
}

bool UMeleeUtils::AddWeapon(USceneComponent* target, UPARAM(meta=(AllowAbstract = "UMeleeWeapon")) USceneComponent* weapon, const FString& socket)
{
    bool result = false;

    // check attached
    TArray<USceneComponent*> parents;
    weapon->GetParentComponents(parents);
    if (parents.FindByPredicate([&](USceneComponent* p){
        return p == target && weapon->GetAttachSocketName().ToString() == socket;
    }))
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon: %s aready attached!"), *weapon->GetName());
        return result;
    }

    // attach
    result = weapon->AttachToComponent(target, FAttachmentTransformRules::SnapToTargetIncludingScale, FName(*socket));

    return result;
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