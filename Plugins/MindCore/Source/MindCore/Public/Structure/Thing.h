/*
    Author: baihan 
    class purpose: Mark for every thing that can be recognized by Mind
*/
#pragma once

#include "CoreMinimal.h"
#include "Thing.generated.h"

UCLASS(Blueprintable)
class MINDCORE_API UThing : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    FString Type;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    FString ID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    int Priority;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    TSubclassOf<UObject> TargetType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    FString Description;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    bool Disappear;
};