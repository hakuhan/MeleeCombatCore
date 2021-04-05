/*
    Author: baihan 
    class purpose: Basic mind which provide baisc AI
*/

#pragma once

#include "Components/ActorComponent.h"

#include "Core/MindInterface.h"
#include "Core/WishInterface.h"
#include "Core/BehaviorInterface.h"
#include "Core/ImagineInterface.h"
#include "Core/RememberInterface.h"
#include "Core/ActionInterface.h"
#include "Core/MindComponentInterface.h"
#include "Structure/BehaviorEvent.h"
#include "Mind.generated.h"

UCLASS(Blueprintable, ClassGroup = (Mind), meta = (BlueprintSpawnableComponent))
class MINDCORE_API UMind : public UActorComponent, public IMindInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, meta = (MustImplement = "RememberInterface"))
    TSubclassOf<UObject> RememberClass;
    UPROPERTY(BlueprintReadWrite)
    TScriptInterface<IRememberInterface> Remember;

    UPROPERTY(EditAnywhere, meta = (MustImplement = "WishInterface"))
    TSubclassOf<UObject> WishClass;
    UPROPERTY(BlueprintReadWrite)
    TScriptInterface<IWishInterface> Wish;
    
    UPROPERTY(EditAnywhere, meta = (MustImplement = "BehaviorInterface"))
    TSubclassOf<UObject> BehaviorClass;
    UPROPERTY(BlueprintReadWrite)
    TScriptInterface<IBehaviorInterface> Behavior;
    
    UPROPERTY(EditAnywhere, meta = (MustImplement = "ImagineInterface"))
    TSubclassOf<UObject> ImagineClass;
    UPROPERTY(BlueprintReadWrite)
    TScriptInterface<IImagineInterface> Imagine;

public:
    void BeginPlay() override;
    void BeginDestroy() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Basic Mind")
    virtual void DoWish_Implementation() override;
    UFUNCTION(BlueprintCallable, Category = "Basic Mind")
    virtual void DoBehavior_Implementation() override;
    UFUNCTION(BlueprintCallable, Category = "Basic Mind")
    virtual void DoImagine_Implementation() override;

    UFUNCTION(BlueprintCallable, Category = "Basic Mind")
    void GetRemember_Implementation(TScriptInterface<IRememberInterface>& outRemember)
    {
        outRemember = Remember;
    }

    template <typename T>
    bool IsMemberValid(TScriptInterface<T> interface)
    {
        bool result = true;

        if (interface == nullptr || interface.GetObject() == nullptr)
        {
            result = false;
            UE_LOG(LogTemp, Warning, TEXT("Mind component mission: %s"), typeid(T).name());
        }

        return result;
    }
};