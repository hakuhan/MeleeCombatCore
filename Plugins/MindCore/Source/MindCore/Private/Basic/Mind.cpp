#include "Basic/Mind.h"

void UMind::BeginPlay()
{
    Super::BeginPlay();

    auto rememberObj = NewObject<UObject>(this, RememberClass);
    auto wishObj = NewObject<UObject>(this, WishClass);
    auto behaviorObj = NewObject<UObject>(this, BehaviorClass);
    auto imagineObj = NewObject<UObject>(this, ImagineClass);

    if (Remember == nullptr || Wish == nullptr || Behavior == nullptr || Imagine == nullptr)
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

void UMind::BeginDestroy()
{
    Super::BeginDestroy();
    if (Wish.GetObject())
        IMindComponentInterface::Execute_OnStop(Wish.GetObject());
    if (Remember.GetObject())
        IMindComponentInterface::Execute_OnStop(Remember.GetObject());
    if (Behavior.GetObject())
        IMindComponentInterface::Execute_OnStop(Behavior.GetObject());
    if (Imagine.GetObject())
        IMindComponentInterface::Execute_OnStop(Imagine.GetObject());
}

void UMind::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    DoWish();
    DoBehavior();
    DoImagine();
}

void UMind::DoWish_Implementation()
{
    if (IsMemberValid(Wish))
    {
        Wish->UpdateWish();
    }
}

void UMind::DoBehavior_Implementation()
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
