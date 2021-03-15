#include "Basic/BasicRemenber.h"

UBasicRemenber::UBasicRemenber()
{
    m_CurrentIndex = -1;
}

UBasicRemenber::~UBasicRemenber()
{
}

void UBasicRemenber::UpdateRemember_Implementation()
{

}

void UBasicRemenber::CreateMemory_Implementation(UMemoryFragment *outMemory)
{
    UMemoryFragment* fragment = NewObject<UMemoryFragment>();
    m_Memories.Add(fragment);
    outMemory = outMemory;
}

void UBasicRemenber::Remember_Implementation(const FString& memoryID, UMemoryFragment *outfragment)
{
    for (auto fragment : m_Memories)
    {
        if (fragment->thingType == memoryID)
        {
            outfragment = fragment;
            break;
        }
    }
}

bool UBasicRemenber::Forget_Implementation(const FString& memoryID)
{
    bool result = false;
    // if (Contains_Implementation(memoryID))
    // {
    //     m_Memories->fragments.RemoveAll([=](const UMemoryFragment *memory) { return memoryID == memory->thingType; });
    //     result = true;
    // }

    return result;
}

bool UBasicRemenber::Save_Implementation(const UMemoryFragment *fragment)
{
    // TODO save game
    return false;
}

bool UBasicRemenber::Share_Implementation(const FString& memoryID, const TScriptInterface<IRemember> &target)
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

void UBasicRemenber::Accept_Implementation(const FString& memoryID, const UMemoryFragment* inMemory)
{
    UMemoryFragment* memory = const_cast<UMemoryFragment*>(inMemory);
    m_Memories.Add(memory);
}

void UBasicRemenber::Clean()
{
    m_Memories.Empty();
}
