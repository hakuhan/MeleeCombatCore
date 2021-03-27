#include "Basic/Mind.h"

void UMind::BeginPlay()
{
    Super::BeginPlay();

    auto rememberObj = NewObject<UObject>(this, RememberClass);
    if (rememberObj != nullptr)
    {
        Remember.SetObject(rememberObj);
        Remember.SetInterface(dynamic_cast<IRememberInterface*>(rememberObj));
    }

    auto wishObj = NewObject<UObject>(this, WishClass);
    if (wishObj != nullptr)
    {
        Wish.SetObject(wishObj);
        Wish.SetInterface(dynamic_cast<IWishInterface*>(wishObj));
    }

    auto behaviorObj = NewObject<UObject>(this, BehaviorClass);
    if (behaviorObj != nullptr)
    {
        Behavior.SetObject(behaviorObj);
        Behavior.SetInterface(dynamic_cast<IBehaviorInterface*>(behaviorObj));
    }

    auto imagineObj = NewObject<UObject>(this, ImagineClass);
    if (imagineObj != nullptr)
    {
        Imagine.SetObject(imagineObj);
        Imagine.SetInterface(dynamic_cast<IImagineInterface*>(imagineObj));
    }

    if (Remember == nullptr || Wish == nullptr || Behavior == nullptr || Imagine == nullptr)
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
    if (IsMemberValid(Wish))
    {
        Wish->UpdateWish();
    }
}

void UMind::DoPlan_Implementation()
{
    if (IsMemberValid(Behavior))
    {
        Behavior->Behave();
    }
}

void UMind::DoImagine_Implementation()
{
    Imagine->Imaging();
}

#pragma endregion