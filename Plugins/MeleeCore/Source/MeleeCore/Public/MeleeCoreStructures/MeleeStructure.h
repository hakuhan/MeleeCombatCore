/*
    Author: baihan 
    class purpose: define Melee structures 
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/EngineTypes.h"
#include "MeleeStructure.generated.h"

UENUM(BlueprintType)
enum class EMeleeHurt : uint8
{
	VERY_LIGHT_HURT,
	LIGHT_HURT,
	MIDEUM_HURT,
	STRONG_HURT,
	VERY_STRONG_HURT,
	SUPER_HURT
};

UENUM(BlueprintType, Meta = (Bitflags))
enum class EAttackWeapon : uint8
{
	Melee_None,
	Melee_All,
	Melee_LeftHand,
	Melee_RightHand,
	Melee_LeftFoot,
	Melee_RightFoot,
	// Melee_None = 0,
	// Melee_All = (1 << 0),
	// Melee_LeftHand = (1 << 1),
	// Melee_RightHand = (1 << 2),
	// Melee_LeftFoot = (1 << 3),
	// Melee_RightFoot = (1 << 4),
};

/*
* weapon hurt type
*/
UENUM(BlueprintType)
enum class ECombatSolution : uint8
{
	ONCE_SOLUTION,
	MULTI_SOLUTION
};

UENUM(BlueprintType)
enum class ECombatHitResult : uint8
{
	NO_HIT,
	NO_INJURY_HIT,
	HURT_HIT,
	DEAD_HIT,
	DEFEND_HIT,
};

// Weapon data structure
USTRUCT(BlueprintType)
struct MELEECORE_API FMeleeWeaponInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EAttackWeapon weaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FName> socketNames;

	UPROPERTY(VisibleAnywhere)
	TArray<FVector> tempSocketLocation;

public:
	FMeleeWeaponInfo() {}
	FMeleeWeaponInfo(EAttackWeapon defaultWeaponType, TArray<FName> defaultSoketNames)
	{
		weaponType = defaultWeaponType;
		socketNames = defaultSoketNames;
	}
	~FMeleeWeaponInfo()
	{
		socketNames.Empty();
		tempSocketLocation.Empty();
	}
};

// Melee structure
USTRUCT(BlueprintType)
struct MELEECORE_API FMeleeSolutionTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECombatSolution solutionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MustImplement = "MeleeSolution"))
	TSubclassOf<UObject> solutionClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle hurtTable;
};

// deal data
USTRUCT(BlueprintType)
struct MELEECORE_API FHurt : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMeleeHurt hurtType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float hurts;

public:
	~FHurt()
	{
	}
};

USTRUCT(BlueprintType)
struct MELEECORE_API FHurtMulti : public FHurt
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float interval;

public:
	~FHurtMulti()
	{
	}
};