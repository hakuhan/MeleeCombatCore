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

UCLASS(Blueprintable)
class ULinkInfo : public UThing
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    int priority;

    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    ELinkState state;
};

UCLASS(Blueprintable)
class ULinkThing : public UThing
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LinkThing")
    TArray<ULinkInfo*> links;
};
