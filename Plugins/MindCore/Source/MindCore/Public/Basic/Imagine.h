#pragma once

#include "Core/ImagineInterface.h"
#include "Core/MindComponentInterface.h"
#include "Imagine.generated.h"

UCLASS(Blueprintable)
class MINDCORE_API UImagine : public UObject, public IImagineInterface, public IMindComponentInterface
{
    GENERATED_BODY()
public:
    UMind *Mind;

    void Imaging_Implementation();

    void JoinWish_Implementation(TScriptInterface<IWishInterface> &wish);

    void JoinBehavior_Implementation(TScriptInterface<IBehaviorInterface> &plan);

    void JoinAction_Implementation(TScriptInterface<IActionInterface> &acton);

    void JoinMemory_Implementation(TScriptInterface<IRememberInterface> &remember);

#pragma region mind component
    virtual void OnInit_Implementation(UMind *mind) override
    {
        Mind = mind;
    }
    virtual void OnStop_Implementation() override {}
#pragma endregion
};