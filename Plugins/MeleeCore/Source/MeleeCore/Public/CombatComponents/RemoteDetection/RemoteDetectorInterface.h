#pragma once

#include "RemoteDetectorInterface.generated.h"

struct FDetectInfo;


DECLARE_DELEGATE_OneParam(FOnRemoteHit, const FDetectInfo&)

UINTERFACE(Blueprintable)
class MELEECORE_API URemoteDetector : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API IRemoteDetector
{
    GENERATED_BODY()
public:

    virtual void BindHitEvent(const FOnRemoteHit& callback);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RemoteDetection")
    void StartDetection();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RemoteDetection")
    void StopDetection();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RemoteDetection")
    void UpdateShape();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RemoteDetection")
    void UpdateSize();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RemoteDetection")
    void PlayHitEffect();
    
};