#include "Basic/Remember.h"

URemenber::URemenber()
{
    m_CurrentIndex = -1;
}

bool URemenber::Remember_Implementation(const UMemoryFragment* target)
{
    if (!m_Memories.Contains(target))
    {
        m_Memories.Add(const_cast<UMemoryFragment*>(target));
        return true;
    }
    return false;
}

bool URemenber::Remind_Implementation(const FString& thingID, UMemoryFragment *outfragment)
{
    bool result = false;
    int targetIndex = FindIndex(thingID);

    if (targetIndex > -1)
    {
        result = true;
        outfragment = m_Memories[targetIndex];
    }

    return result;
}

bool URemenber::Forget_Implementation(const FString& thingID)
{
    bool result = false;
    int targetIndex = FindIndex(thingID);

    if (targetIndex >= 0)
    {
        m_Memories.RemoveAt(targetIndex);
        result = true;
    }

    return result;
}

bool URemenber::Share_Implementation(const FString &memoryName, const TScriptInterface<IRememberInterface> &target)
{
    bool result = false;
    int targetIndex = FindIndex(memoryName);
    
    if (targetIndex >= 0 && target.GetObject() != nullptr)
    {
        // Get memory
        UMemoryFragment *memoryFragment = m_Memories[targetIndex];

        // Send
        target->Accept(memoryName, memoryFragment);
        result = true;
    }

    return result;
}

void URemenber::Accept_Implementation(const FString &thingID, const UMemoryFragment *inMemory)
{
    UMemoryFragment* memory = const_cast<UMemoryFragment*>(inMemory);
    m_Memories.Add(memory);
}

void URemenber::Clean()
{
    m_Memories.Empty();
}

int URemenber::FindIndex(const FString& memoryName)
{
    return m_Memories.IndexOfByPredicate([&](UMemoryFragment* memory){
        return memory->Name == memoryName;
    });
}
