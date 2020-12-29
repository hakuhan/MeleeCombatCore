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
	Melee_LeftHand,
	Melee_RightHand,
	Melee_LeftFoot,
	Melee_RightFoot,
};

/*
* weapon hurt type
*/
UENUM(BlueprintType)
enum class EDetectionSolution : uint8
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

// Melee structure
USTRUCT(BlueprintType)
struct MELEECORE_API FCombatSolutionTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDetectionSolution solutionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MustImplement = "CombatSolution"))
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