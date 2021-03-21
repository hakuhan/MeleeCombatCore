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
    UExecutorInfo* m_Info;

    UFUNCTION(BlueprintCallable)
    void Init(UExecutorInfo* info)
    {
        m_Info = info;
    }
};