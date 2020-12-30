#pragma once
#include "CoreMinimal.h"
#include "MeleeDetection/MeleeWeaponInfo.h"
#include "MeleeUtils.generated.h"

class UDetectMelee;

UCLASS(ClassGroup = (Custom), meta = (MeleeUtils))
class MELEECORE_API UMeleeUtils : public UObject
{
    GENERATED_BODY()

public:
    /** Find implementation of interface at actor*/
    UFUNCTION(BlueprintCallable)
    static void GetImplementFromActor(AActor *owner, TSubclassOf<UInterface> interface, TArray<UObject *> &array, bool checkSelf = true);

    // Control weapon state of detect melee
    UFUNCTION(BlueprintCallable)
	static bool EnableWeaponByType(UDetectMelee *detectMelee, UPARAM(meta=(Bitmask, UseEnumValuesAsMaskValuesInEditor="true", BitmaskEnum=EAttackWeapon)) uint8 WeaponType, bool enable = true, bool refreshWeapons = true);

    // template <typename InterfaceType>
    // typedef void (InterfaceType::*InterfaceFunc)(AActor *caller, ...);
    // DECLARE_DYNAMIC_DELEGATE_OneParam(FCallInterfaceDelegate, bool, isOn);

    // /** Call interface function at actor*/
    // // UFUNCTION(BlueprintCallable)
    // template <typename InterfaceType>
    // static void CallInterfaceFromActor(AActor *actor, TScriptInterface<InterfaceType> interface, UMeleeUtils::FCallInterfaceDelegate function , bool value);
    // // static void CallInterfaceFromActor(AActor *actor, TScriptInterface<InterfaceType> interface, void (InterfaceType::*func) (UObject* obj, ParamType arg) , ParamType data);
};