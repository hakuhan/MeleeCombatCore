#pragma once

#include "CoreMinimal.h"

#include "Core/Wish.h"
#include "BasicWish.generated.h"

UCLASS(Blueprintable)
class MINDCORE_API UBasicWish : public UObject, public IWish
{
    GENERATED_BODY()
public:
    virtual void CreateWish_Implementation(UThing* outWishes);
    virtual void UpdateWish_implementaion();
};

