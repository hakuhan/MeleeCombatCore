#include "MotionRule/MotionRuleBase.h"

UMotionRuleBase::UMotionRuleBase()
{
    m_CurrentId = -1;
    m_Type = EMotionType::MOTION_DOWN_PRIOR;
}

void UMotionRuleBase::UpdateType(EMotionType type)
{
    m_Type = type;
}

void UMotionRuleBase::RegistRules(const TMap<int, int> &rules)
{
    EmptyRules();
    m_Rules.Append(rules);
}

void UMotionRuleBase::EmptyRules()
{
    m_Rules.Empty();
}

bool UMotionRuleBase::RegistMotion(int id, int level)
{
    bool result = false;

    if (!m_Rules.Contains(id))
    {
        m_Rules.Add(id, level);
        result = true;
    }

    return result;
}

bool UMotionRuleBase::RemoveMotion(int id)
{
    bool result = false;

    if (m_Rules.Contains(id))
    {
        m_Rules.Remove(id);
    }

    return result;
}

bool UMotionRuleBase::UpdateMotion(int id, int newLevel)
{
    bool result = false;

    if (m_Rules.Contains(id))
    {
        m_Rules[id] = newLevel;
        result = true;
    }

    return result;
}

void UMotionRuleBase::RemoveCheckEvent_Implementation(int id)
{
    if (m_ExtendRules.Contains(id))
    {
        m_ExtendRules.Remove(id);
    }
}

bool UMotionRuleBase::IsSwitchable_Implementation(int id)
{
    bool result = true;

    if (m_Rules.Contains(id))
    {
        if (!m_Rules.Contains(m_CurrentId))
        {
            result = true;
        }
        else
        {
            switch (m_Type)
            {
            case EMotionType::MOTION_TOP_PRIOR:
                if (m_Rules[id] <= m_Rules[m_CurrentId])
                {
                    result = true;
                }
                break;

            case EMotionType::MOTION_DOWN_PRIOR:
                if (m_Rules[id] >= m_Rules[m_CurrentId])
                {
                    result = true;
                }
                break;

            default:
                break;
            }
        }
    }

    if (result && m_ExtendRules.Contains(id))
    {
        result = m_ExtendRules[id].Execute();
    }

    return result;
}

bool UMotionRuleBase::SwitchMotion_Implementation(int id)
{
    bool result = true;

    if (m_Rules.Contains(id))
    {
        m_CurrentId = id;
        result = true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Rule:%d doesn't exists!"), id);
    }

    return result;
}

void UMotionRuleBase::AddCheckEvent_Implementation(int id, const FMotionRuleDelegate &event)
{
    m_ExtendRules.Add(id, event);
}
