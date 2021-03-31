/*
    Author: baihan 
    class purpose: execute unit 
*/

#pragma once

#include "ActionInterface.generated.h"

UENUM(BlueprintType)
enum class EActionState : uint8
{
    Action_Inactive UMETA(DisplayName = "Inactive"),
    Action_Unreachable UMETA(DisplayName = "unreachable"),
    Action_Active UMETA(DisplayName = "Active"),
    Action_Success UMETA(DisplayName = "Success"),
    Action_Failure UMETA(DisplayName = "Failure"),
};

UINTERFACE(Blueprintable)
class MINDCORE_API UActionInterface : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IActionInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
    void Init(AActor* owner);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
    void PrepareAction();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
    void RunningAction();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
    void FinishAction();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
    EActionState GetState();
};