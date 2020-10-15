/*
    Author: baihan 
    class purpose: Skill system editor
*/

#pragma once

#include "CoreMinimal.h"
#include "AnimGraphNode_Base.h"
#include "Animation/AnimNodeBase.h"
#include "AnimNodes/AnimNode_SkillSystem.h"
#include "AnimGraphNode_SkillSystem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MELEECORE_API UAnimGraphNode_SkillSystem : public UAnimGraphNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Skill")
	FAnimNode_SkillSystem m_Node;

	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetTooltipText() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	//~ End UEdGraphNode Interface.

	//~ Begin UAnimGraphNode_Base Interface
	virtual FString GetNodeCategory() const override;
	//~ End UAnimGraphNode_Base Interface
};
