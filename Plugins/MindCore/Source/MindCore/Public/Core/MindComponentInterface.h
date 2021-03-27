#pragma once
#include "Basic/Mind.h"
#include "MindComponentInterface.generated.h"

UINTERFACE(Blueprintable)
class MINDCORE_API UMindComponentInterface : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IMindComponentInterface
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void OnInit(UMind* mind);
  
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mind")
    void OnStop();
};