#pragma once

#include "CoreMinimal.h"
#include "SkillComponent/SkillInfo.h"
#include "Engine/DataTable.h"
#include "SkillLineInfo.generated.h"

USTRUCT(BlueprintType)
struct FSkillLineInfo
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkillLine)
    FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkillLine)
    TArray<FSkillInfo> SkillLine;
};