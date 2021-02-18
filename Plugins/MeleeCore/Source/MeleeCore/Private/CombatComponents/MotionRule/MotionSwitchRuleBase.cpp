#include "MotionRule/MotionSwitchRuleBase.h"

void UMotionSwitchRuleBase::UpdateMotions(const TArray<int> &rules)
{
    m_SwitchList.Empty();
    m_SwitchList.Append(rules);
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

bool UMotionSwitchRuleBase::RemoveMotion(int id)
{
    bool result = false;

    if (m_SwitchList.Contains(id))
    {
        m_SwitchList.Remove(id);
        result = true;
    }

    return result;
}

void UMotionSwitchRuleBase::AddRule(int id, const FMotionRuleDelegate &event)
{
    m_Rules.Add(id, event);
}

void UMotionSwitchRuleBase::RemoveRule(int id)
{
    if (m_Rules.Contains(id))
    {
        m_Rules.Remove(id);
    }
}

bool UMotionSwitchRuleBase::IsSwitchable_Implementation(int id)
{
    bool result = false;

    if (m_SwitchList.Contains(id))
    {
        result = true;
    }

    if (result && m_Rules.Contains(id))
    {
        result = m_Rules[id].Execute();
    }

    return result;
}