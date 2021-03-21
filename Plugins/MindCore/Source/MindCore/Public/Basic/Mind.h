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

#include "Mind.generated.h"

UCLASS(ClassGroup = (Mind), meta = (BlueprintSpawnableComponent))
class MINDCORE_API UMind : public UActorComponent, public IMindInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IRememberInterface> m_Remember;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IWishInterface> m_Wish;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IBehaviorInterface> m_Behavior;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IImagineInterface> m_Imagine;

public:
    void BeginPlay() override;
    void BeginDestroy() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Basic Mind")
    virtual void DoWish_Implementation() override;
    UFUNCTION(BlueprintCallable, Category = "Basic Mind")
    virtual void DoPlan_Implementation() override;
    UFUNCTION(BlueprintCallable, Category = "Basic Mind")
    virtual void DoImagine_Implementation() override;

    UFUNCTION(BlueprintCallable, Category = "Basic Mind")
    void GetRemember_Implementation(TScriptInterface<IRememberInterface>& outRemember)
    {
        outRemember = m_Remember;
    }

    template <typename T>
    bool IsMemberValid(TScriptInterface<T> interface)
    {
        bool result = true;

        if (interface == nullptr || interface.GetObject() == nullptr)
        {
            result = false;
            UE_LOG(LogTemp, Warning, TEXT("Mind Interface mission: %s"), typeid(T).name());
        }

        return result;
    }
};