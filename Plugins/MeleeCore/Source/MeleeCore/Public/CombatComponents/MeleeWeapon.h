// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeleeCoreStructures/MeleeStructure.h"
#include "Components/MeshComponent.h"
#include "MeleeWeapon.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MELEECORE_API UMeleeWeapon : public UMeshComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMeleeWeaponInfo info;
	FMeleeWeaponInfo* infoPtr;

public:
	UMeleeWeapon();
	bool IsTargetWeapon(uint8 weaponMask);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
};
