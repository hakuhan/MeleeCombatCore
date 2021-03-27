/*
    Author: baihan 
    class purpose: Mark for every thing that can be recognized by Mind
*/
#pragma once

#include "CoreMinimal.h"
#include "Thing.generated.h"

USTRUCT(Blueprintable)
struct MINDCORE_API FThing
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thing")
    FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thing")
    FString Type;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thing")
    int Number;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thing")
    bool NeverEnding;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thing")
    FString Description;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thing")
    int Priority;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thing")
    TSubclassOf<UObject> TargetType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thing")
    bool Disappearance;
};