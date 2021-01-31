#include "MeleeDetection/MeleeWeapon.h"

#pragma region SimpleWeapon
USimpleWeapon::USimpleWeapon()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USimpleWeapon::BeginPlay()
{
	Super::BeginPlay();

	m_Info.SocketNames.Empty();
	m_Info.SocketNames.Append(GetAllSocketNames());
}

#pragma endregion

#pragma region SkeletalWeapon

USkeletalWeapon::USkeletalWeapon()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USkeletalWeapon::BeginPlay()
{
	Super::BeginPlay();

	m_Info.SocketNames.Empty();
	m_Info.SocketNames.Append(GetAllSocketNames());
}

#pragma endregion

#pragma region InvisibleWeapon

UInvisibleWeapon::UInvisibleWeapon()
{
	PrimaryComponentTick.bCanEverTick = false;
	m_SocketName = TEXT("InvisibleWeapon");
}

void UInvisibleWeapon::BeginPlay()
{
	Super::BeginPlay();

	m_Info.SocketNames.Empty();
	m_Info.SocketNames.Add(m_SocketName);
}

#pragma endregion