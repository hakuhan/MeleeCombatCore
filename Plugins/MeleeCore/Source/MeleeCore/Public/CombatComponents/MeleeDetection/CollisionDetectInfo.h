#pragma once

#include "CoreMinimal.h"

#include "CollisionDetectInfo.generated.h"

UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ECollisionDetectType : uint8
{
    NONE = 0 UMETA(Hidden),
    SPHERE_DETECT = 1 << 0 UMETA(DisplayName="Sphere"),
    COLUMN_DETECT = 1 << 1 UMETA(DisplayName="Column"),
};

USTRUCT(BlueprintType)
struct FCollisionDetectInfo : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CollisionDetect)
    ECollisionDetectType Type;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=CollisionDetect)
    bool IsShowCollision;

};
