#include "MotionRule/MotionRuleBase.h"

UMotionRuleBase::UMotionRuleBase()
{
    PrimaryComponentTick.bCanEverTick = false;
    m_bRuleActive = false;
    m_CurrentLevel = -1;
    m_Type = EMotionType::MOTION_DOWN_PRIOR;
}

void UMotionRuleBase::BeginPlay()
{
    Super::BeginPlay();

    UpdateRuleWithName(m_Table.RowName);
}

void UMotionRuleBase::UpdateRuleWithName(const FName &name)
{
    auto rulePtr = m_Table.DataTable->FindRow<FMotionRuleTable>(name, "Find motion rule", true);
    if (rulePtr)
    {
        m_Type = rulePtr->Type;
        m_Motions = rulePtr->Rules;
        m_CurrentRuleName = name;
    }
}

void UMotionRuleBase::UpdateType(EMotionType type)
{
    m_Type = type;
}

bool UMotionRuleBase::RegistMotion(int level, const FString &key)
{
    bool result = false;
    int index = m_Motions.IndexOfByPredicate([&](const FMotionRuleItem &_motion) {
        return _motion.Level == level && _motion.Key == key;
    });

    if (index < 0)
    {
        m_Motions.Add(FMotionRuleItem(level, key));
        result = true;
    }

    return result;
}

bool UMotionRuleBase::RemoveMotion(const FString &key)
{
    bool result = false;
    int index = m_Motions.IndexOfByPredicate([&](const FMotionRuleItem &_motion) {
        return _motion.Key == key;
    });

    if (index >= 0)
    {
        m_Motions.RemoveAt(index);
    }

    return result;
}

bool UMotionRuleBase::GetLevel(const FString &key, int &outLevel)
{
    bool result = false;
    int index = m_Motions.IndexOfByPredicate([&](const FMotionRuleItem &_motion) {
        return _motion.Key == key;
    });

    if (index >= 0)
    {
        outLevel = m_Motions[index].Level;
        result = true;
    }

    return result;
}

bool UMotionRuleBase::UpdateMotion(const FString &Key, int newLevel)
{
    bool result = false;
    int index = m_Motions.IndexOfByPredicate([&](const FMotionRuleItem &_motion) {
        return _motion.Key == Key;
    });

    if (index >= 0)
    {
        m_Motions[index].Level = newLevel;
        result = true;
    }

    return result;
}

bool UMotionRuleBase::IsRuleActive_Implementation()
{
    return m_bRuleActive;
}

void UMotionRuleBase::SetRuleActive_Implementation(bool bActive)
{
    m_bRuleActive = bActive;
}

bool UMotionRuleBase::IsSwitchable_Implementation(int level)
{
    return m_CurrentLevel <= level;
}

bool UMotionRuleBase::SwitchMotion_Implementation(int level)
{
    bool result = true;

    int index = m_Motions.IndexOfByPredicate([&](const FMotionRuleItem &_motion) {
        return _motion.Level == level;
    });

    if (index >= 0)
    {
        m_CurrentLevel = level;
        result = true;
        UE_LOG(LogTemp, Warning, TEXT("Switch level:%d"), level);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Rule:%s doesn't contains level %d"), *m_CurrentRuleName.ToString(), level);
    }

    return result;
}
