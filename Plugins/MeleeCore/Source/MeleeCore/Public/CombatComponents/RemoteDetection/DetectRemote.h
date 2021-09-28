#pragma once

#include "CoreMinimal.h"
#include "RemoteDetectorInterface.h"
#include "DetectRemote.generated.h"

UENUM(BlueprintType)
enum class ERemoteDetector : uint8
{
    ATTACH_DETECTOR UMETA(DisplayName="Attach to actor"),
    MOVABLE_DETECTOR UMETA(DisplayName="Move ifself")
};

USTRUCT(BlueprintType)
struct FDetectRemoteInfo
{
    GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DetectRemote, meta = (MustImplement = "RemoteDetector"))
    TSubclassOf<UObject> DetectorClass;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DetectRemote)
    ERemoteDetector Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DetectRemote)
    AActor* AttachTarget;
};

UCLASS(Blueprintable, classGroup = (MeleeCore), meta = (BlueprintSpawnableComponent))
class MELEECORE_API UDetectRemote : public UActorComponent
{
    GENERATED_BODY()
public:
    UDetectRemote();

    UFUNCTION(BlueprintCallable, Category = "RemoteDetection")
    void Launch(const FDetectRemoteInfo& info);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    void OnHit(const FDetectInfo& info);

};