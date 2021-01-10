#pragma once

#include "CoreMinimal.h"
#include "DetectSolution.h"
#include "CollisionDetectInfo.h"

#include "CollisionDetect.generated.h"


UCLASS()
class MELEECORE_API UCollisionDetect : public UObject, public IDetectSolution
{
    GENERATED_BODY()
public:

    FCollisionDetectInfo m_Info;

    void Init(FDataTableRowHandle table) override
    {

    }

    bool Detect(AActor* const current, FVector curDetectPos, FVector preDetectPos, TArray<FDetectInfo>& outDetect, const bool IsCheckPerframe) override
    {
        return false;
    }

    void SetDebug(bool debugMode) override
    {
        m_Info.IsShowCollision = debugMode;
    }
};