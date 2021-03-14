#pragma once

#include "Structure/Thing.h"
#include "Structure/LinkThing.h"
#include "Connection.generated.h"

UCLASS(Blueprintable)
class MINDCORE_API UConnection : public UThing
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")
    TArray<ULinkThing*> things;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")
    FString firstThing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")
    FString targetThing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")
    FString currentThing;
};