/*
	Author: baihan 
	class purpose: Mark Melee weapon 
*/


#include "MeleeComponents/MeleeWeapon.h"

// Sets default values for this component's properties
UMeleeWeapon::UMeleeWeapon()
{
	PrimaryComponentTick.bCanEverTick = false;

	infoPtr = new FMeleeWeaponInfo();
	info = *(infoPtr);
}


// Called when the game starts
void UMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();

	info.socketNames.Append(GetAllSocketNames());
}

void UMeleeWeapon::BeginDestroy()
{
	Super::BeginDestroy();

	delete infoPtr;
}

bool UMeleeWeapon::IsTargetWeapon(uint8 weaponMask)
{
	return weaponMask & info.weaponType;
}
