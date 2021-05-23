#include "Basic/Mind.h"

void UMind::BeginPlay()
{
    Super::BeginPlay();

    auto rememberObj = NewObject<UObject>(this, RememberClass);
    auto wishObj = NewObject<UObject>(this, WishClass);
    auto behaviorObj = NewObject<UObject>(this, BehaviorClass);
    auto imagineObj = NewObject<UObject>(this, ImagineClass);

    if (rememberObj == nullptr || wishObj == nullptr || behaviorObj == nullptr || imagineObj == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Mind should be initialized!"));
    }
    else
    {
        Remember.SetObject(rememberObj);
        Remember.SetInterface(dynamic_cast<IRememberInterface *>(rememberObj));

        Wish.SetObject(wishObj);
        Wish.SetInterface(dynamic_cast<IWishInterface *>(wishObj));

        Behavior.SetObject(behaviorObj);
        Behavior.SetInterface(dynamic_cast<IBehaviorInterface *>(behaviorObj));

        Imagine.SetObject(imagineObj);
        Imagine.SetInterface(dynamic_cast<IImagineInterface *>(imagineObj));
        IMindComponentInterface::Execute_OnInit(wishObj, this);
        IMindComponentInterface::Execute_OnInit(rememberObj, this);
        IMindComponentInterface::Execute_OnInit(behaviorObj, this);
        IMindComponentInterface::Execute_OnInit(imagineObj, this);
    }
}

void UMind::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    Execute_DoWish(this);
    Execute_DoBehavior(this);
    Execute_DoImagine(this);
}

void UMind::DoWish_Implementation()
{
    if (IsMemberValid(Wish))
    {
        IWishInterface::Execute_UpdateWish(Wish.GetObject());
    }
}

void UMind::DoBehavior_Implementation()
{
    if (IsMemberValid(Behavior))
    {
        IBehaviorInterface::Execute_Behave(Behavior.GetObject());
    }
}

void UMind::DoImagine_Implementation()
{
    if (IsMemberValid(Imagine))
    {
        IImagineInterface::Execute_Imaging(Imagine.GetObject());
    }
}
