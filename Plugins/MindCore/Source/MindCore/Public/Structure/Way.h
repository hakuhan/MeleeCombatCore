/*
    Author: baihan 
    class purpose: Superintend data
*/

#pragma once

#include "CoreMinimal.h"
#include "Structure/Thing.h"
#include "Structure/ActionBasis.h"
#include "Way.generated.h"

UCLASS(Blueprintable)
class UWay : public UThing
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Way")
    FString Connection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Way")
    TArray<UActionBasis*> usingActions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Way")
    int currentIndex;
};