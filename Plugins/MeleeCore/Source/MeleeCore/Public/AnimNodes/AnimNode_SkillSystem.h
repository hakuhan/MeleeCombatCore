/*
    Author: baihan 
    class purpose: Skill system logic 
*/

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "AnimNode_SkillSystem.generated.h"

USTRUCT(BlueprintType)
struct MELEECORE_API FAnimNode_SkillSystem : public FAnimNode_Base
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
    FPoseLink BasePose;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta=(PinShownByDefault))
    bool startSkill;

    // Interface to implement
    virtual void Initialize_AnyThread(const FAnimationInitializeContext &Context);
    virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext &Context);
    virtual void Update_AnyThread(const FAnimationUpdateContext &Context);
    virtual void Evaluate_AnyThread(FPoseContext &Output);
    virtual void GatherDebugData(FNodeDebugData &DebugData);
};