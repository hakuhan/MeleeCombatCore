/*
    Author: baihan 
    class purpose: Basic mind which provide baisc AI
*/

#pragma once

#include "Components/ActorComponent.h"

#include "Core/MindInterface.h"
#include "Core/WishInterface.h"
#include "Core/PlanInterface.h"
#include "Core/ImagineInterface.h"
#include "Core/RememberInterface.h"

#include "Mind.generated.h"

UCLASS(ClassGroup = (Mind), meta = (BlueprintSpawnableComponent))
class MINDCORE_API UMind : public UActorComponent, public IMindInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IRememberInterface> m_remember;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IWishInterface> m_wish;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IPlanInterface> m_plan;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IImagineInterface> m_imagine;

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
    virtual void DoRemember_Implementation() override;

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