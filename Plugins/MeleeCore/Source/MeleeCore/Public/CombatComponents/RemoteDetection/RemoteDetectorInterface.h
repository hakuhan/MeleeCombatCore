#pragma once

#include "MeleeDetection/DetectSolution.h"
#include "DetectSolutions/CombatSolution.h"
#include "RemoteDetectorInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnRemoteHit, const FDetectInfo&, detectInfo, const FHurt&, hurt);

UINTERFACE(Blueprintable)
class MELEECORE_API URemoteDetector : public UInterface
{
    GENERATED_BODY()
};

class MELEECORE_API IRemoteDetector
{
    GENERATED_BODY()
public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RemoteDetection")
    void InitData(const FHurt& hurt, const FOnRemoteHit& callback);
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
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RemoteDetection")
    bool IsFinished();
};