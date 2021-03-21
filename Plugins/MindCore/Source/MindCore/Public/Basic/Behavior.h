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
class MINDCORE_API UMindBehaviorInfo : public UThing
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UThing* m_Wish;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBehaviorState m_State;
};

UCLASS(BlueprintType)
class MINDCORE_API UBehavior : public UObject, public IBehaviorInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    UMindBehaviorInfo* m_Info;

public:
    virtual void Behave_Implementation() override;
};