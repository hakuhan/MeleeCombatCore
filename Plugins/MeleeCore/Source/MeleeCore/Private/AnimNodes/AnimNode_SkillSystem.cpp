#include "AnimNodes/AnimNode_SkillSystem.h"


void FAnimNode_SkillSystem::Initialize_AnyThread(const FAnimationInitializeContext &Context)
{
    BasePose.Initialize(Context);
}

void FAnimNode_SkillSystem::CacheBones_AnyThread(const FAnimationCacheBonesContext &Context)
{
    BasePose.CacheBones(Context);
}

void FAnimNode_SkillSystem::Update_AnyThread(const FAnimationUpdateContext &Context)
{
    // EvaluateGraphExposedInputs.Execute(Context);
    BasePose.Update(Context);
}

void FAnimNode_SkillSystem::Evaluate_AnyThread(FPoseContext &Output)
{
    BasePose.Evaluate(Output);
}

void FAnimNode_SkillSystem::GatherDebugData(FNodeDebugData &DebugData)
{
    FString DebugLine = DebugData.GetNodeName(this);


    DebugData.AddDebugItem(DebugLine);

    BasePose.GatherDebugData(DebugData);
}