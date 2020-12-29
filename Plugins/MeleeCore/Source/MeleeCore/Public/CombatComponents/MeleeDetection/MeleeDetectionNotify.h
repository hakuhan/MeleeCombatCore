// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "Curves/CurveFloat.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MeleeDetection/DetectMelee.h"
#include "MeleeDetection/MeleeEffect.h"
#include "MeleeDetectionNotify.generated.h"

/**
 * 
 */
UCLASS()
class MELEECORE_API UMeleeDetectionNotify : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UDetectMelee *m_MeleeCombat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	EMeleeHurt m_Hurt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	EDetectionSolution m_Solution;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UCurveFloat *m_HurtCurve;
	// Working weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (BItmask, BitmaskEnum = "EAttackWeapon"))
	uint8 m_WeaponFlags;
	UPROPERTY()
	float m_TotalDuration = 0;
	UPROPERTY()
	float m_TimeBuffer = 0;

public:
	UMeleeDetectionNotify();
	void BeginDestroy() override;
	virtual void NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation);
};
