/*
    Author: baihan 
    class purpose: define Combat structures 
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/EngineTypes.h"
#include "CombatStructure.generated.h"

// detect Weapon data structure
USTRUCT(Blueprintable)
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
};

// Deal structure
USTRUCT(Blueprintable)
struct MELEECOMBATCORE_API FCombatSolution : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MustImplement = "HitSolution"))
	TSubclassOf<UObject> solutionClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle solutionInfo;
};


// deal data
USTRUCT(Blueprintable)
struct MELEECOMBATCORE_API FHitSolutionInfo : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    FHitSolutionInfo()
        : hurts(1)
    {
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float hurts;
};