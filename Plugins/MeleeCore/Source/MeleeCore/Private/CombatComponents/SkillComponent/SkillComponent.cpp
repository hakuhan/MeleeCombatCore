#include "SkillComponent/SkillComponent.h"

void USkillComponent::BeginPlay()
{
    Super::BeginPlay();
    
    InitInfo();

    m_Data = FSkillComponentData(m_debug);

    m_LineControl = NewObject<USkillLine>();
    m_LineControl->OnChangeState.BindUObject(this, &USkillComponent::OnSkillUpdate);
    if (m_Info.SkillLines.Num() > 0)
    {
        m_LineControl->UpdateInfo(m_Info.SkillLines[0], GetOwner(), m_Data.DynamicData);
        m_Data.LineIndex = 0;
    }
}

bool USkillComponent::SwitchSkill(const FString& lineName, const FString& skillName, bool bForce)
{
    bool result = false;
    int index = m_Info.SkillLines.IndexOfByPredicate([&](const FSkillLineInfo& _line){
        return _line.Name == lineName;
    });

    if (index >= 0)
    {
        if (bForce || !m_LineControl->IsExecuting() || m_LineControl->CanSwitch())
        {
            m_LineControl->OnSwitchOut();

            if (m_Data.LineIndex != index)
            {
                m_LineControl->UpdateInfo(m_Info.SkillLines[index], GetOwner(), m_Data.DynamicData);
                m_Data.LineIndex = index;
            }
            
            result = m_LineControl->StartLine(skillName);
        }

    }

    return result;
}

bool USkillComponent::ExecuteSkill()
{
    bool result = false;

    switch (m_Data.State)
    {
        case ESkillState::SKILL_UNSTART:
        case ESkillState::SKILL_TERMINAl:
            m_LineControl->StartLine(FString());
            result = true;
            break;
        
        case ESkillState::SKILL_EXECUTING:
            result = m_LineControl->SwitchWithRule();
        break;

        default:
            break;
    }

    return result;
}

bool USkillComponent::IsExecuting()
{
    return m_LineControl->IsExecuting();
}

bool USkillComponent::IsSwitchable(const FString& lineName)
{
    bool result = false;

    if (IsCurrentSkillLine(lineName))
    {
        result = !m_LineControl->IsExecuting() || m_LineControl->CanSwitch();
    }

    return result;
}


void USkillComponent::StopSkill(bool bRule, const FAlphaBlend& InBlendOut)
{
    if (IsExecuting())
    {
        m_LineControl->FinishSkill(bRule, InBlendOut);
    }
}

void USkillComponent::SkillEnded()
{
    if (m_Data.DynamicData)
    {
        m_Data.DynamicData->IsSkillLineEnd = true;
    }
    OnSkillEnded(m_LineControl->m_Info.Name);
    
    if (OnSkllEndEvent.IsBound())
    {
        OnSkllEndEvent.Broadcast(m_LineControl->m_Info.Name);
    }
}

void USkillComponent::OnSkillUpdate(ESkillLineState lineState)
{
    switch (lineState)
    {
    case ESkillLineState::SKILL_LINE_PLAYING:
        m_Data.State = ESkillState::SKILL_EXECUTING;
        break;

    case ESkillLineState::SKILL_LINE_FINISHED:
        m_Data.State = ESkillState::SKILL_TERMINAl;
        break;
    
    default:
        break;
    }
}

bool USkillComponent::IsCurrentSkillLine(const FString& lineName)
{
    bool result = false;

    if (!lineName.IsEmpty() && m_Info.SkillLines.IsValidIndex(m_Data.LineIndex))
    {
        result = m_Info.SkillLines[m_Data.LineIndex].Name == lineName;
    }

    return result;
}
