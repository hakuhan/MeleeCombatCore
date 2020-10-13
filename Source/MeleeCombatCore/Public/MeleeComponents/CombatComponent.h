/*
	Author: baihan 
	class purpose: main interface of attack detection 
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HitSolution.h"
#include "CombatStructure.h"
#include "HitReaction.h"
#include "CombatEffectComponent.h"
#include "CombatComponent.generated.h"

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class MELEECOMBATCORE_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// deal handler
	UPROPERTY()
	TScriptInterface<IHitSolution> m_solution;
	UPROPERTY()
	TArray<AActor*> m_tempHitActors;

public:
#pragma region types
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Detection")
	ECombatHurt m_DefaultHurt;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Detection")
	ECombatHurt m_HurtType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Detection")
	ECombatSolution m_DefaultSolution;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Detection")
	ECombatSolution m_SolutionType;
#pragma endregion

	// solution
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	FDataTableRowHandle m_SolutionTable;

	UPROPERTY(VisibleAnywhere, Category = "Detection")
	UCombatEffectComponent* m_EffectComponent;

	// tag to find out weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	TArray<FString> m_weaponTargs;

	// weapon data
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Detection")
	TArray<FCombatWeapon> m_weapons;

	UPROPERTY(VisibleAnywhere, Category = "Detection")
	bool m_isDetecting;

#pragma region Debug
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	bool m_isShowTrace;
#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection", meta = (Bitmask, BitmaskEnum = "ECollisionChannel"))
	TEnumAsByte<ECollisionChannel> m_channel;

public:
	// Sets default values for this component's properties
	UCombatComponent();
	void BeginDestroy() override;

	/*
	Change hurt type
	*/
	UFUNCTION(BlueprintCallable)
	void UpdateHurts(ECombatHurt newHurt, ECombatSolution newSolution);

	UFUNCTION(BlueprintCallable)
	void UpdateHurtRate(float rate);

	UFUNCTION(BlueprintCallable)
	void ResetHurts();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
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

private:
	void ExecuteHit(FHitResult hit);
};
