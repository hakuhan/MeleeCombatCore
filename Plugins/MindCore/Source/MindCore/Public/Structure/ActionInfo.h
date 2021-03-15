/*
    Author: baihan 
    class purpose: Action basis data 
*/

#pragma once

#include "Structure/Thing.h"
#include "ActionInfo.generated.h"

UENUM(BlueprintType)
enum class EActionState : uint8
{
    Action_Inactive UMETA(DisplayName = "Inactive"),
    Action_Unreachable UMETA(DisplayName = "unreachable"),
    Action_Active UMETA(DisplayName = "Active"),
    Action_Success UMETA(DisplayName = "Success"),
    Action_Failure UMETA(DisplayName = "Failure"),
};

UCLASS(Blueprintable)
class UActionInfo : public UThing
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActionBasis")
    TArray<UThing*> cost;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActionBasis")
    TArray<UThing*> reward;
};