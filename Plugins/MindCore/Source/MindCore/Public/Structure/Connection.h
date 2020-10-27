#pragma once

#include "Structure/Thing.h"
#include "Structure/LinkThing.h"
#include "Connection.generated.h"

USTRUCT(BlueprintType)
struct MINDCORE_API FConnection : public FThing
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")
    TArray<FLinkThing> things;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")
    FString firstThing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")
    FString targetThing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")
    FString currentThing;
};