/*
    Author: baihan 
    class purpose: Action basis data 
*/

#pragma once

#include "Structure/Thing.h"
#include "ActionBasis.generated.h"

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
struct FActionBasis : public FThing
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActionBasis")
    int priority;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActionBasis")
    EActionState state;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActionBasis")
    FString preThing;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActionBasis")
    FString targetThing;
};