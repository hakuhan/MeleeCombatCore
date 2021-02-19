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

void UMotionSwitchRuleBase::UpdateAllRules(const TMap<int, FMotionRuleEvent>& rules)
{
    m_Rules.Empty();

    for (auto _rule : rules)
    {
        m_Rules.Add(_rule.Key, _rule.Value.Callback);
    }
}

void UMotionSwitchRuleBase::UpdateRule(int id, const FMotionRuleDelegate& event)
{
    if (m_Rules.Contains(id))
    {
        m_Rules[id] = event;
    }
    else
    {
        m_Rules.Add(id, event);
    }
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

    if (m_Rules.Contains(id))
    {
        result = m_Rules[id].Execute();
    }

    return result;
}