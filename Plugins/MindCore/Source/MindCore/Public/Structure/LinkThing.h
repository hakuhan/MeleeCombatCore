/*
    Author: baihan 
    class purpose: To be used in Connection
*/

#pragma once

#include "Structure/Thing.h"
#include "LinkThing.generated.h"

UENUM(BlueprintType)
enum class ELinkState : uint8
{
    Link_Unkown UMETA(DisplayName = "Unkown"),
    Link_Linking UMETA(DisplayName = "Linking"),
    Link_Break UMETA(DisplayName = "Break"),
};

USTRUCT(BlueprintType)
struct FLinkInfo : public FThing
{
    GENERATED_USTRUCT_BODY()

public:
    int linkID;
    int priority;
    ELinkState state;
};

USTRUCT(BlueprintType)
struct FLinkThing : public FThing
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LinkThing")
    TArray<FLinkInfo> links;
};
