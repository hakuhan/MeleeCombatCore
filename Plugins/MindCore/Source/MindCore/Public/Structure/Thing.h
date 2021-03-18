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
    FString thingType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    FString name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    int priority;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    TSubclassOf<UObject> targetType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    FString Description;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Thing")
    bool Disappear;
};