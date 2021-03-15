/*
    Author: baihan 
    class purpose: Mind memory data 
*/

#pragma once

#include "CoreMinimal.h"

#include "Structure/Thing.h"

#include "MemoryFragment.generated.h"

UENUM(BlueprintType)
enum class EMemoryState : uint8
{
    Memory_Empty UMETA(DisplayName="Empty"),
    Memory_Creating UMETA(DisplayName="Creating"),
    Memory_Happy UMETA(DisplayName="Happy"),
    Memory_Satisfy UMETA(DisplayName="Satisfy"),
    Memory_Insensible UMETA(DisplayName="Insensible"),
    Memory_Contrived UMETA(DisplayName="Contrived"),
    Memory_Sad UMETA(DisplayName="Sad"),
};

UCLASS(Blueprintable)
class MINDCORE_API UMemoryFragment : public UThing
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory")
    EMemoryState memoryState;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory")
    TArray<UThing*> things;
};