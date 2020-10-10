/*
	Author: baihan 
	class purpose: Shake Actor bone when attacked
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShakeBoneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MELEECOMBATCORE_API UShakeBoneComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShakeBoneComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ShakeBone(FVector worldLocation);

	UFUNCTION(BlueprintCallable)
	void ShakeBone(FString boneName);
};
