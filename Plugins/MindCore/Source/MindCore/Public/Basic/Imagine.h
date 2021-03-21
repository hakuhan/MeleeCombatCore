#pragma once

#include "Core/ImagineInterface.h"
#include "Imagine.generated.h"

UCLASS()
class MINDCORE_API UImagine : public UObject, public IImagineInterface
{
    GENERATED_BODY()
public:
    void Imaging_Implementation();

    void JoinWish_Implementation(TScriptInterface<IWishInterface>& wish);

    void JoinBehavior_Implementation(TScriptInterface<IBehaviorInterface>& plan);

    void JoinAction_Implementation(TScriptInterface<IActionInterface>& acton);

    void JoinMemory_Implementation(TScriptInterface<IRememberInterface>& remember);
};