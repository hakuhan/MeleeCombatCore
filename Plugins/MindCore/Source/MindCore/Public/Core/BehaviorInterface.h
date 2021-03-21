#pragma once

#include "BehaviorInterface.generated.h"

UINTERFACE()
class MINDCORE_API UBehaviorInterface : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IBehaviorInterface
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void Behave();
};