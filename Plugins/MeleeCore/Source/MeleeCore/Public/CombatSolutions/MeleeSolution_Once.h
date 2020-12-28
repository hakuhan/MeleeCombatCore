/*
    Author: baihan 
    class purpose: hand hit event once every animation 
*/
#pragma once
#include "CoreMinimal.h"
#include "MeleeSolution.h"
#include "MeleeSolution_Once.generated.h"

UCLASS(Blueprintable)
class MELEECORE_API UMeleeSolution_Once : public UObject, public IMeleeSolution
{
    GENERATED_BODY()

private:
    TArray<AActor *> m_Actors;

public:
    ~UMeleeSolution_Once();
    virtual void OnHit_Implementation(AActor *attackedActor, ECombatHitResult &outResult) override;

    virtual void InitData_Implementation() override;

    virtual void OnStartDetection_Implementation() override;

    virtual void OnEndDetection_Implementation() override;
};