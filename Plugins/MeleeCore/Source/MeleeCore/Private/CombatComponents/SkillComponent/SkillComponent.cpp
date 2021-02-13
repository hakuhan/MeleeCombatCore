#include "SkillComponent/SkillComponent.h"

void USkillComponent::BeginPlay()
{
    Super::BeginPlay();
    m_Info = *(m_InfoTable.GetRow<FSkillTable>("Get Skill line"));
    m_Data = FSkillComponentData();

    m_LineControl = NewObject<USkillLine>();
    m_LineControl->OnChangeState.BindUObject(this, &USkillComponent::OnSkillUpdate);
    if (m_Info.SkillLines.Num() > 0)
    {
        m_LineControl->UpdateInfo(m_Info.SkillLines[0], GetOwner(), m_Data.DynamicData);
        m_Data.LineIndex = 0;
    }
}

void USkillComponent::BeginDestroy()
{
    Super::BeginDestroy();
}

bool USkillComponent::SwitchSkillWithRule(const FString& lineName, const FString& skillName)
{
    bool result = false;
    int index = m_Info.SkillLines.IndexOfByPredicate([&](const FSkillLineInfo& _line){
        return _line.Name == lineName;
    });

    if (index >= 0)
    {
        if (!m_LineControl->IsExecuting() || m_LineControl->CanSwitch())
        {
            m_LineControl->OnSwitchOut();

            m_LineControl->UpdateInfo(m_Info.SkillLines[index], GetOwner(), m_Data.DynamicData);
            m_LineControl->StartLine(skillName);
            m_Data.LineIndex = index;
            result = true;
        }
    }

    return result;
}

bool USkillComponent::SwitchSkill(const FString& lineName, const FString& skillName)
{
    bool result = false;
    int index = m_Info.SkillLines.IndexOfByPredicate([&](const FSkillLineInfo& _line){
        return _line.Name == lineName;
    });

    if (index >= 0)
    {
        if (m_LineControl->IsExecuting())
        {
            m_LineControl->OnSwitchOut();
        }

        m_LineControl->UpdateInfo(m_Info.SkillLines[index], GetOwner(), m_Data.DynamicData);
        m_Data.LineIndex = index;
        result = m_LineControl->StartLine(skillName);
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
            UE_LOG(LogTemp, Warning, TEXT("Start Skill"));
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

bool USkillComponent::IsSkillLineSwitchable(const FString& skillLineName)
{
    bool result = false;
    int index = m_Info.SkillLines.IndexOfByPredicate([&](const FSkillLineInfo& _line){
        return _line.Name == skillLineName;
    });

    if (m_Data.LineIndex == index)
    {
        result = !m_LineControl->IsExecuting() || m_LineControl->CanSwitch();
    }

    return result;
}


bool USkillComponent::ExecuteSkillLine(const FString& skillLineName)
{
    bool result = false;
    if (IsCurrentSkillLine(skillLineName))
    {
        result = ExecuteSkill();
    }
    else
    {
        result = SwitchSkillWithRule(skillLineName, FString());
    }
    
    return result;
}


void USkillComponent::StopSkill(bool terminate, const FAlphaBlend& InBlendOut)
{
    if (IsExecuting())
    {
        m_LineControl->FinishSkill(terminate, InBlendOut);
    }
}

void USkillComponent::OnSkillUpdate(ESkillLineState lineState)
{
    switch (lineState)
    {
    case ESkillLineState::SKILL_LINE_PLAYING:
        m_Data.State = ESkillState::SKILL_EXECUTING;
        UE_LOG(LogTemp, Warning, TEXT("Executing Skill"));
        break;

    case ESkillLineState::SKILL_LINE_FINISHED:
        UE_LOG(LogTemp, Warning, TEXT("Skill End"));
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
