// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ActorComponent.h"
#include "MeleeEffect.h"
#include "DetectTypes.h"
#include "CombatSolution.h"
#include "MeleeWeapon.h"
#include "DetectMelee.generated.h"

/*
* weapon hurt type
*/
UENUM(BlueprintType)
enum class EDetectionSolution : uint8
{
	ONCE_SOLUTION,
	MULTI_SOLUTION
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
	uint8 m_WeaponMask;

#pragma region Tick caches
	UPROPERTY()
	FMeleeWeaponInfo m_WeaponInfoTemp;
	UPROPERTY()
	FWeaponData m_WeaponDataTemp;
	UPROPERTY()
	TArray<FHitResult> m_Hits;
	UPROPERTY()
	TArray<AActor *> m_IgnoreActors;
#pragma endregion

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	FLinearColor m_TraceColor = FLinearColor::Green;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	FLinearColor m_HittedColor = FLinearColor::Red;

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

	UFUNCTION(BlueprintCallable)
	void GetWeapons(TArray<TScriptInterface<IMeleeWeapon>>& outWeapons)
	{
		outWeapons = m_MeleeWeapons;
	}

	/// <summary>
	/// Update weapon and slot info
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void UpdateWeapon();
#pragma endregion

private:
	void ExecuteHit(FHitResult hit);
};
