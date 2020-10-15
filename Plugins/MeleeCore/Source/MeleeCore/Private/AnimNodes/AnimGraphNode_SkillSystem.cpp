// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNodes/AnimGraphNode_SkillSystem.h"

#define LOCTEXT_NAMESPACE "SkillNode"

FLinearColor UAnimGraphNode_SkillSystem::GetNodeTitleColor() const
{
    return FLinearColor::Green;
}

FText UAnimGraphNode_SkillSystem::GetTooltipText() const
{
    return LOCTEXT("SkillNode", "SkillNode");
}

FText UAnimGraphNode_SkillSystem::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return LOCTEXT("SkillNode", "SkillNode");
}

FString UAnimGraphNode_SkillSystem::GetNodeCategory() const
{
    return TEXT("SkillNode");
}