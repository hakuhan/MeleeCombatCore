#pragma once

#include "MeleeWeaponInfo.generated.h"

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