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
	// deal info
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	FDataTableRowHandle m_hitSolutionInfo;

	UPROPERTY(VisibleAnywhere, Category = "Detection")
	UCombatEffectComponent* m_effectComponent;

	// tag to find out weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	TArray<FString> m_weaponTargs;

	// weapon data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	TArray<FCombatWeapon> m_weapons;

	UPROPERTY(VisibleAnywhere, Category = "Detection")
	bool m_isDetecting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	bool m_isShowTrace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection", meta = (Bitmask, BitmaskEnum = "ECollisionChannel"))
	TEnumAsByte<ECollisionChannel> m_channel;

public:
	// Sets default values for this component's properties
	UCombatComponent();
	void BeginDestroy() override;

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

	UFUNCTION(BlueprintCallable)
	void UpdateSolution(TScriptInterface<IHitSolution> solution);

private:
	void ExecuteHit(FHitResult hit);
};
