#pragma once
#include "CoreMinimal.h"
#include "MeleeUtils.generated.h"

UCLASS(ClassGroup = (Custom), meta = (MeleeUtils))
class MELEECORE_API UMeleeUtils : public UObject
{
    GENERATED_BODY()

public:
    /* Find implementation of interface at actor*/
    UFUNCTION(BlueprintCallable)
    static void GetImplementFromActor(AActor *owner, TSubclassOf<UInterface> interface, TArray<UObject *> &array, bool checkSelf = true);
};