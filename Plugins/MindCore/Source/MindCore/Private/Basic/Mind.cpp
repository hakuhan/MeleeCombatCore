#include "Basic/Mind.h"

void UMind::BeginPlay()
{
    Super::BeginPlay();

    auto rememberObj = NewObject<UObject>(this, RememberClass);
    if (rememberObj != nullptr)
    {
        m_Remember.SetObject(rememberObj);
        m_Remember.SetInterface(dynamic_cast<IRememberInterface*>(rememberObj));
    }

    auto wishObj = NewObject<UObject>(this, WishClass);
    if (wishObj != nullptr)
    {
        m_Wish.SetObject(wishObj);
        m_Wish.SetInterface(dynamic_cast<IWishInterface*>(wishObj));
        m_Wish->Reset();
    }

    auto behaviorObj = NewObject<UObject>(this, BehaviorClass);
    if (behaviorObj != nullptr)
    {
        m_Behavior.SetObject(behaviorObj);
        m_Behavior.SetInterface(dynamic_cast<IBehaviorInterface*>(behaviorObj));
    }

    auto imagineObj = NewObject<UObject>(this, ImagineClass);
    if (imagineObj != nullptr)
    {
        m_Imagine.SetObject(imagineObj);
        m_Imagine.SetInterface(dynamic_cast<IImagineInterface*>(imagineObj));
    }

    if (m_Remember == nullptr || m_Wish == nullptr || m_Behavior == nullptr || m_Imagine == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Mind should be initialized!"));
    }
}

void UMind::BeginDestroy()
{
    Super::BeginDestroy();
}

void UMind::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

#pragma region Mind

void UMind::DoWish_Implementation()
{
    if (IsMemberValid(m_Wish))
    {
        m_Wish->UpdateWish();
    }
}

void UMind::DoPlan_Implementation()
{
    if (IsMemberValid(m_Behavior))
    {
        m_Behavior->Behave();
    }
}

void UMind::DoImagine_Implementation()
{
    m_Imagine->Imaging();
}

#pragma endregion