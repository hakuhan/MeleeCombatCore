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
        m_Remember.SetObject(wishObj);
        m_Remember.SetInterface(dynamic_cast<IWishInterface*>(wishObj));
    }
    auto behaviorObj = NewObject<UObject>(this, BehaviorClass);
    if (behaviorObj != nullptr)
    {
        m_Remember.SetObject(behaviorObj);
        m_Remember.SetInterface(dynamic_cast<IBehaviorInterface*>(behaviorObj));
    }
    auto imagineObj = NewObject<UObject>(this, ImagineClass);
    if (imagineObj != nullptr)
    {
        m_Remember.SetObject(imagineObj);
        m_Remember.SetInterface(dynamic_cast<IImagineInterface*>(imagineObj));
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