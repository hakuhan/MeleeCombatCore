#include "SkillComponent/SkillLine.h"

void USkillLine::Tick(float DeltaTime)
{
    if (!m_DynamicData)
    {
        return;
    }

    if (m_DynamicData->IsSkillLineEnd)
    {
        UpdateState(ESkillLineState::SKILL_LINE_FINISHED);
        m_Data.IsEnable = false;
    }
}

void USkillLine::UpdateInfo(const FSkillLineInfo &info, AActor* target, ASkillDynamicData* dynamicData)
{
    m_Info = info;
    m_Target = target;
    m_DynamicData = dynamicData;
}

bool USkillLine::SwitchSkill(const FString& Name)
{
    int index = m_Info.SkillLine.IndexOfByPredicate([&](const FSkillInfo& _info){
        return _info.Name == Name;
    });

    return SwitchSkillByIndex(index);
}

bool USkillLine::StartLine(const FString& skillName)
{
    bool result = false;
    if (skillName.IsEmpty())
    {
        result = SwitchSkillByIndex(0);
        UE_LOG(LogTemp, Warning, TEXT("Begin Skill line: %s"), *(m_Info.Name));
    }
    else
    {
        result = SwitchSkill(skillName);
    }

    if (result)
    {
        m_Data.Record.SkillLine.Empty();
        UpdateState(ESkillLineState::SKILL_LINE_PLAYING);
        m_Data.IsEnable = true;
    }

    return result;
}

bool USkillLine::SwitchWithRule()
{
    bool result = false;
    if (CanSwitch())
    {
        result = NextSkill();
        UE_LOG(LogTemp, Warning, TEXT("Switch Skill : %s, %d"), *(m_Info.Name), result);
    }

    return result;
}

bool USkillLine::NextSkill()
{
    bool result = false;
    if (m_Info.SkillLine.IsValidIndex(m_Data.SkillOffset + 1))
    {
        result = SwitchSkillByIndex(m_Data.SkillOffset + 1);
    }

    return result;
}

bool USkillLine::IsExecuting()
{
    return m_Data.State == ESkillLineState::SKILL_LINE_PLAYING;
}

bool USkillLine::IsEndSkillLine()
{
    return m_Data.State == ESkillLineState::SKILL_LINE_FINISHED;
}

void USkillLine::FinishSkill(bool terminate, const FAlphaBlend& InBlendOut)
{
    FSkillInfo skillInfo;
    bool isInfoOk = GetCurrentSkillInfo(skillInfo);
    if (isInfoOk)
    {
        auto skill = GetSkill(skillInfo, false);
        if (skill)
        {
            if (terminate)
            {
                skill->Terminate();
            }
            else
            {
                skill->Stop(InBlendOut);
            }
        }
    }
    UpdateState(ESkillLineState::SKILL_LINE_FINISHED);
}

bool USkillLine::CanSwitch()
{
    bool result = false;
    FSkillInfo skillInfo;
    bool isInfoOk = GetCurrentSkillInfo(skillInfo);
    if (isInfoOk)
    {
        USkill* _skill = GetSkill(skillInfo, false);

        if (_skill)
        {
            result = _skill->CanSwitch();
        }
    }

    return result;
}

bool USkillLine::SwitchSkillByIndex(int index)
{
    if (m_Info.SkillLine.IsValidIndex(index))
    {
        USkill* skill = GetSkill(m_Info.SkillLine[index]);
        skill->ExecuteSkill(m_Target);
        
        m_DynamicData->IsSkillLineEnd = false;
        m_Data.SkillOffset = index;
        m_Data.Record.SkillLine.Add(m_Info.SkillLine[index]);
        return true;
    }

    return false;
}

void USkillLine::OnSwitchOut()
{
    UpdateState(ESkillLineState::SKILL_LINE_JUMPED);
}

void USkillLine::GetSkillRecord(FSkillLineInfo& records)
{
    records = m_Data.Record;
}

bool USkillLine::IsCurrentSkillOver()
{
    bool result = false;
    if (m_Data.State != ESkillLineState::SKILL_LINE_UNSTART)
    {
        auto _skill = m_Data.GetCurrentSkill();
        if (_skill)
        {
            result = _skill->m_Data.ExecuteState == ESkillExecuteState::SKILL_EXECUTE_END;
        }
    }

    return result;
}

USkill* USkillLine::GetSkill(const FSkillInfo& skillInfo, bool bCreateNew)
{
    USkill* result = nullptr;
    int index = m_Data.Skills.IndexOfByPredicate([&](USkill* _skill){
        return _skill->IsMatch(skillInfo);
    });
    if (index >= 0)
    {
        result = m_Data.Skills[index];
    }
    else if (bCreateNew)
    {
        USkill* _skill = NewObject<USkill>();
        m_Data.Skills.Add(_skill);
        _skill->UpdateData(skillInfo, m_DynamicData);
        result = _skill;
    }

    return result;
}

bool USkillLine::GetCurrentSkillInfo(FSkillInfo& outInfo)
{
    bool result = false;

    if (m_Info.SkillLine.IsValidIndex(m_Data.SkillOffset))
    {
        outInfo = m_Info.SkillLine[m_Data.SkillOffset];
        result = true;
    }

    return result;
}

void USkillLine::UpdateState(ESkillLineState state)
{
    m_Data.State = state;
    OnChangeState.ExecuteIfBound(state);
}

