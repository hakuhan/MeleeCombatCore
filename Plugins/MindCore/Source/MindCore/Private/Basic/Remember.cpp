#include "Basic/Remember.h"

URemenber::URemenber()
{
    m_CurrentIndex = -1;
}

void URemenber::Remember_Implementation(const FString& thingID, UMemoryFragment *outfragment)
{
    outfragment = *m_Memories.FindByPredicate([&](UMemoryFragment* memory){
        return memory->ID == thingID;
    });
}

bool URemenber::Forget_Implementation(const FString& thingID)
{
    bool result = false;
    int targetIndex = m_Memories.IndexOfByPredicate([&](UMemoryFragment* memory){
        return memory->ID == thingID;
    });

    if (targetIndex >= 0)
    {
        m_Memories.RemoveAt(targetIndex);
        result = true;
    }

    return result;
}

bool URemenber::Save_Implementation(const FString& thingID)
{
    // TODO save game
    return false;
}

bool URemenber::Share_Implementation(const FString &thingID, const TScriptInterface<IRememberInterface> &target)
{
    bool result = false;
    // if (Contains_Implementation(memoryID) && target.GetObject() != nullptr)
    // {
    //     // Get memory
    //     UMemoryFragment *memoryFragment = NewObject<UMemoryFragment>();
    //     GetMemory(memoryID, memoryFragment);

    //     // Send
    //     target->Accept(memoryID, memoryFragment);
    //     result = true;
    // }

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
