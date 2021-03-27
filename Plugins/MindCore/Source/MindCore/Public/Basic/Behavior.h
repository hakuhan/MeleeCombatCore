/*
    Author: baihan 
    Date: "2021-03-21" 
    Class discription: Base class that achieve wishes
*/

#pragma once

#include "CoreMinimal.h"
#include "Core/BehaviorInterface.h"
#include "Structure/Thing.h"
#include "Behavior.generated.h"

UENUM(BlueprintType)
enum class EBehaviorState : uint8
{
    BEHAVIOR_READY UMETA(DisplayName="Ready"),
    BEHAVIOR_EXECUTING UMETA(DisplayName="Executing"),
    BEHAVIOR_FINISH UMETA(DisplayName="Finish"),
};

UCLASS(BlueprintType)
class MINDCORE_API UBehavior : public UObject, public IBehaviorInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
    EBehaviorState m_State;

public:
    virtual void Behave_Implementation() override;
};