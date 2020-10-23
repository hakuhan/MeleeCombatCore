#pragma once

#include "Structure/Thing.h"
#include "Connection.generated.h"

USTRUCT(BlueprintType)
struct MINDCORE_API FConnection : public FThing
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Connection")
    TArray<int> things;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Connection")
    int firstThingID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Connection")
    int targetThingID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Connection")
    int currentThingID;
};