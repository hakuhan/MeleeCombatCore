/*
    Author: baihan 
    Date: "2021-03-16" 
    Class discription: Base action implements IActionInterface 
*/

#pragma once

#include "CoreMinimal.h"
#include "Core/ActionInterface.h"
#include "BasicAction.generated.h"

UENUM(BlueprintType)
enum class EActionState : uint8
{
    Action_Inactive UMETA(DisplayName = "Inactive"),
    Action_Unreachable UMETA(DisplayName = "unreachable"),
    Action_Active UMETA(DisplayName = "Active"),
    Action_Success UMETA(DisplayName = "Success"),
    Action_Failure UMETA(DisplayName = "Failure"),
};

USTRUCT(BlueprintType)
struct MINDCORE_API FActionInfo
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    EActionState m_State;
};

UCLASS(Blueprintable)
class MINDCORE_API UBasicAction : public UObject, public IActionInterface
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    FActionInfo m_Info;

    virtual void PrepareAction_Implementation();
    virtual void RunningAction_implementation();
    virtual void FinishAction_Implementation();

    void Init(const FActionInfo& info);
};