#include "Basic/Remenber.h"

URemenber::URemenber()
{
    m_CurrentIndex = -1;
}

URemenber::~URemenber()
{
}

void URemenber::Remember_Implementation(const FString& thingID, UMemoryFragment *outfragment)
{
    for (auto fragment : m_Memories)
    {
        if (fragment->thingType == thingID)
        {
            outfragment = fragment;
            break;
        }
    }
}

bool URemenber::Forget_Implementation(const FString& thingID)
{
    bool result = false;
    // if (Contains_Implementation(memoryID))
    // {
    //     m_Memories->fragments.RemoveAll([=](const UMemoryFragment *memory) { return memoryID == memory->thingType; });
    //     result = true;
    // }

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
