// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "MeleeUtils.h"
#include "ComboInterface.h"
#include "AnimNotify_MeleeComboOver.generated.h"

/**
 * 
 */
UCLASS()
class MELEECORE_API UAnimNotify_MeleeComboOver : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
