/*
    Author: baihan 
    class purpose: define Combat structures 
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/EngineTypes.h"
#include "CombatStructure.generated.h"

UENUM(BlueprintType)
enum class ECombatHurt : uint8
{
	veryLight,
	light,
	midum,
	strong,
	veryStrong,
	super
};

/*
* weapon hurt type
*/
UENUM(BlueprintType)
enum class ECombatSolution : uint8
{
	once,
	multi
};

// detect Weapon data structure
USTRUCT(BlueprintType)
struct MELEECOMBATCORE_API FCombatWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	UMeshComponent *weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> socketNames;

	UPROPERTY(VisibleAnywhere)
	TArray<FVector> tempSocketLocation;

public:
	~FCombatWeapon()
	{
		weapon = nullptr;
		socketNames.Empty();
		tempSocketLocation.Empty();
	}
};

// Deal structure
USTRUCT(BlueprintType)
struct MELEECOMBATCORE_API FCombatSolution : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECombatSolution solutionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MustImplement = "HitSolution"))
	TSubclassOf<UObject> solutionClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle hurtTable;

public:
	~FCombatSolution()
	{
	}
};

// deal data
USTRUCT(BlueprintType)
struct MELEECOMBATCORE_API FHurt : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECombatHurt hurtType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float hurts;

public:
	~FHurt()
	{
	}
};

USTRUCT(BlueprintType)
struct FHurtMulti : public FHurt
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