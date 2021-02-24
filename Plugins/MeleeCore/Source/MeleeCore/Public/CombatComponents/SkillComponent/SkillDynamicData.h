#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "SkillDynamicData.generated.h"

UENUM(BlueprintType)
enum class ESkillBreakLevel : uint8
{
    SKILL_BREAK_EASY UMETA(DisplayName="轻松"),
    SKILL_BREAK_NORMAL UMETA(DisplayName="正常"),
    SKILL_BREAK_HARD UMETA(DisplayName="困难"),
    SKILL_BREAK_UNABLE UMETA(DisplayName="不可能"),
};

UCLASS(BlueprintType)
class MELEECORE_API ASkillDynamicData : public AInfo
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    bool IsSwitchable = false;
    
    UPROPERTY(BlueprintReadWrite)
    ESkillBreakLevel SkillBreakLevel;

    UPROPERTY(BlueprintReadWrite)
    bool IsSkillLineEnd = false;
        
    UPROPERTY()
    bool bDebug = false;
};