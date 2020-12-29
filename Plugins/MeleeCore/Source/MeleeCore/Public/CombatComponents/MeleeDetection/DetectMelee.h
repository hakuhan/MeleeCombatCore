// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ActorComponent.h"
#include "MeleeEffect.h"
#include "MeleeDetection/DetectSolutions/CombatSolution.h"
#include "MeleeStructure.h"
#include "MeleeWeapon.h"
#include "DetectMelee.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MELEECORE_API UDetectMelee : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TScriptInterface<ICombatSolution> m_CombatSolution;
	UPROPERTY()
	TArray<AActor *> m_HitActorTemps;
	UPROPERTY()
	uint8 m_weaponMask;

public:
#pragma region Solutions
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Melee")
	EMeleeHurt m_DefaultHurt;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Melee")
	EMeleeHurt m_HurtType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Melee")
	EDetectionSolution m_DefaultSolution;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Melee")
	EDetectionSolution m_SolutionType;
#pragma endregion

	// solution
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	FDataTableRowHandle m_CombatSolutionTable;

	UPROPERTY(VisibleAnywhere, Category = "Melee")
	UMeleeEffect *m_EffectComponent;

	// weapon data
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Melee")
	TArray<TScriptInterface<IMeleeWeapon>> m_MeleeWeapons;

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
	UDetectMelee();

#pragma region HurtControl
	/*
	Change hurt
	*/
	UFUNCTION(BlueprintCallable)
	void UpdateHurts(EMeleeHurt newHurt, EDetectionSolution newSolution);

	/* Change hurt rate */
	UFUNCTION(BlueprintCallable)
	void UpdateHurtRate(float rate);

	UFUNCTION(BlueprintCallable)
	void UpdateWeaponMask(uint8 weaponMask);

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
