#include "MotionRule/MotionSwitchRuleBase.h"

void UMotionSwitchRuleBase::UpdateAllMotions(const TArray<int>& motions)
{
    m_SwitchList.Empty();
    m_SwitchList.Append(motions);
}

bool UMotionSwitchRuleBase::AddMotion(int id)
{
    bool result = false;

    if (!m_SwitchList.Contains(id))
    {
        m_SwitchList.Add(id);
        result = true;
    }

    return result;
}

void UMotionSwitchRuleBase::RemoveMotion(int id)
{
    if (m_SwitchList.Contains(id))
    {
        m_SwitchList.Remove(id);
    }
}

void UMotionSwitchRuleBase::UpdateAlternativeRules(const TMap<int, FMotionRuleEvent>& rules)
{
    m_AlternativeRules.Empty();

    for (auto _rule : rules)
    {
        m_AlternativeRules.Add(_rule.Key, _rule.Value.Callback);
    }
}

void UMotionSwitchRuleBase::UpdateBasicRule(int id, const FMotionRuleDelegate& event)
{
    if (m_BasicRules.Contains(id))
    {
        m_BasicRules[id] = event;
    }
    else
    {
        m_BasicRules.Add(id, event);
    }
}

void UMotionSwitchRuleBase::RemoveBasicRule(int id)
{
    if (m_BasicRules.Contains(id))
    {
        m_BasicRules.Remove(id);
    }
}

bool UMotionSwitchRuleBase::IsSwitchable_Implementation(int id)
{
    bool result = CheckMotion(id);

    if (result)
    {
        result = CheckRule(id);
    }

    return result;
}

bool UMotionSwitchRuleBase::CheckMotion(int id)
{
    return m_SwitchList.Contains(id);
}

bool UMotionSwitchRuleBase::CheckRule(int id)
{
    // If rule is not fonded, return true
    bool result = true;

    if (m_BasicRules.Contains(id))
    {
        if (m_AlternativeRules.Contains(id))
            result = m_AlternativeRules[id].Execute();    
        else
            result = m_BasicRules[id].Execute();
    }
    else if (m_AlternativeRules.Contains(id))
    {
        result = m_AlternativeRules[id].Execute();
    }

    return result;
}