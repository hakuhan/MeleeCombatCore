#pragma once

#include "MeleeWeaponInfo.generated.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class EAttackWeapon : uint8
{
	Melee_LeftHand,
	Melee_RightHand,
	Melee_LeftFoot,
	Melee_RightFoot,
};


USTRUCT(BlueprintType)
struct MELEECORE_API FMeleeWeaponInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta=(BItmask,BitmaskEnum="EAttackWeapon"))
	uint8 WeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FName> SocketNames;

public:
	FMeleeWeaponInfo() {}
	~FMeleeWeaponInfo()
	{
		SocketNames.Empty();
	}
};