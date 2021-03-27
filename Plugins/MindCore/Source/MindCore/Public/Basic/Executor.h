#pragma once

#include "CoreMinimal.h"
#include "Core/BehaviorExecutorInterface.h"
#include "Structure/ExecutorInfo.h"
#include "Executor.generated.h"

UCLASS()
class MINDCORE_API UExecutor : public UObject, public IBehaviorExecutorInterface
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadwrite)
    FExecutorInfo m_Info;

    UFUNCTION(BlueprintCallable)
    void Init(const FExecutorInfo& info)
    {
        m_Info = info;
    }
};