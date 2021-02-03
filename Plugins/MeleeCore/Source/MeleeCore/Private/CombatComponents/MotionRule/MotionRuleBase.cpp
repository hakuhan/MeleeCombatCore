#include "MotionRule/MotionRuleBase.h"

UMotionRuleBase::UMotionRuleBase()
{
    m_CurrentLevel = -1;
    m_Type = EMotionType::MOTION_DOWN_PRIOR;
}

void UMotionRuleBase::BeginPlay()
{
    // TODO Init from table
}

void UMotionRuleBase::UpdateType(EMotionType type)
{
    m_Type = type;
}

bool UMotionRuleBase::RegistMotion(int level, const FString& key)
{
    return false;
}

bool UMotionRuleBase::RemoveMotion(const FString& key)
{
    return false;
}

bool UMotionRuleBase::GetLevel(const FString& key, int& outLevel)
{
    return false;
}

bool UMotionRuleBase::UpdateMotion(const FString& Key, int newLevel)
{
    return false;
}

bool UMotionRuleBase::IsRuleActive_Implementation()
{
    return false;
}

void UMotionRuleBase::SetRuleActive_Implementation(bool bActive)
{
    
}

bool UMotionRuleBase::IsSwitchable_Implementation(int type)
{
    return false;
}

bool UMotionRuleBase::SwitchMotion_Implementation(int level)
{
    return false;
}
