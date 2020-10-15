// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ActorComponent.h"
#include "MeleeComponents/MeleeEffect.h"
#include "MeleeSolutions/MeleeSolution.h"
#include "MeleeCoreStructures/MeleeStructure.h"
#include "MeleeCombat.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MELEECORE_API UMeleeCombat : public UActorComponent
{
	GENERATED_BODY()

private:
	// deal handler
	UPROPERTY()
	TScriptInterface<IMeleeSolution> m_MeleeSolution;
	UPROPERTY()
	TArray<AActor *> m_HitActorTemps;

public:
#pragma region types
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Melee")
	EMeleeHurt m_DefaultHurt;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Melee")
	EMeleeHurt m_HurtType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Melee")
	ECombatSolution m_DefaultSolution;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Melee")
	ECombatSolution m_SolutionType;
#pragma endregion

	// solution
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	FDataTableRowHandle m_MeleeSolutionTable;

	UPROPERTY(VisibleAnywhere, Category = "Melee")
	UMeleeEffect *m_EffectComponent;

	// tag to find out weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	TArray<FString> m_MeleeWeaponTargs;

	// weapon data
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Melee")
	TArray<FMeleeWeapon> m_MeleeWeapons;

	UPROPERTY(VisibleAnywhere, Category = "Melee")
	bool m_IsDetecting;

#pragma region Debug
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	bool m_IsShowTrace;
#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee", meta = (Bitmask, BitmaskEnum = "ECollisionChannel"))
	TEnumAsByte<ECollisionChannel> m_Channel;

protected:
	// Called when the game starts
	void BeginPlay() override;
	void BeginDestroy() override;

public:
	// Sets default values for this component's properties
	UMeleeCombat();

#pragma region HurtControl
	/*
	Change hurt
	*/
	UFUNCTION(BlueprintCallable)
	void UpdateHurts(EMeleeHurt newHurt, ECombatSolution newSolution);

	/* Change hurt rate */
	UFUNCTION(BlueprintCallable)
	void UpdateHurtRate(float rate);

	/* Reset hurt to default */
	UFUNCTION(BlueprintCallable)
	void ResetHurts();
#pragma endregion

#pragma region DetectControl
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	// Detection
	UFUNCTION(BlueprintCallable)
	void StartDetection();

	UFUNCTION(BlueprintCallable)
	void EndDetection();

	UFUNCTION(BlueprintCallable)
	void ResetData();

	/// <summary>
	/// Update weapon and slot info
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void UpdateWeapon();
#pragma endregion

private:
	void ExecuteHit(FHitResult hit);
};
