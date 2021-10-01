#pragma once

#include "CoreMinimal.h"
#include "RemoteDetectorInterface.h"
#include "Engine/DataTable.h"
#include "DetectSolutions/CombatSolution.h"

#include "DetectRemote.generated.h"

UENUM(BlueprintType)
enum class ERemoteDetector : uint8
{
    ATTACH_DETECTOR UMETA(DisplayName="Attach to actor"),
    MOVABLE_DETECTOR UMETA(DisplayName="Move ifself")
};

USTRUCT(BlueprintType)
struct FDetectRemoteInfo : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DetectRemote, meta = (MustImplement = "RemoteDetector"))
    TSubclassOf<UObject> DetectorClass;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DetectRemote)
    ERemoteDetector Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DetectRemote)
    FHurt Hurt;
};

UCLASS(Blueprintable, classGroup = (MeleeCore), meta = (BlueprintSpawnableComponent))
class MELEECORE_API UDetectRemote : public UActorComponent
{
    GENERATED_BODY()
public:
    UDetectRemote();

    UFUNCTION(BlueprintCallable, Category = "RemoteDetection")
    UObject* Launch(const FString& remoteName, AActor* attachActor = nullptr);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    void OnHit(const FDetectInfo& info, const FHurt& hurt);

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = DetectRemote)
    FDataTableRowHandle m_Infos;

    UPROPERTY(BlueprintReadWrite)
    TArray<UObject*> m_Detectors;
};