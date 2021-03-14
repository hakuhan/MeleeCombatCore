#include "Basic/BasicRemenber.h"

UBasicRemenber::UBasicRemenber()
{
    m_CurrentIndex = -1;
}

UBasicRemenber::~UBasicRemenber()
{
}

void UBasicRemenber::GetAllWishes_Implementation(TArray<UWishThing*> &outWishes)
{
    outWishes.Empty();

    for (auto memory : m_Memory->fragments)
    {
        outWishes.Add(memory->wishData);
    }
}

void UBasicRemenber::CurrentMemory_Implementation(UMemoryFragment *outFragment)
{
    if (m_CurrentIndex == -1 || m_Memory->fragments.Num() == 0)
    {
        CreateMemory_Implementation(outFragment);
        m_CurrentIndex = 0;
        return;
    }

    if (m_CurrentIndex >= m_Memory->fragments.Num() || m_CurrentIndex < 0)
    {
        m_CurrentIndex = GetFirstMemory(outFragment, true);
    }
}

bool UBasicRemenber::Contains_Implementation(const FString& memoryID)
{
    bool result = false;

    result = m_Memory->fragments.ContainsByPredicate([=](const UMemoryFragment *memory) {
        return memory->thingType == memoryID;
    });

    return result;
}

void UBasicRemenber::CreateMemory_Implementation(UMemoryFragment *outMemory)
{
    UMemoryFragment* fragment = NewObject<UMemoryFragment>();
    m_Memory->fragments.Add(fragment);
    outMemory = outMemory;
}

void UBasicRemenber::GetMemory_Implementation(const FString& memoryID, UMemoryFragment *outMemory)
{
    for (auto fragment : m_Memory->fragments)
    {
        if (fragment->thingType == memoryID)
        {
            outMemory = fragment;
            break;
        }
    }
}

void UBasicRemenber::Store_Implementation(const UMemoryFragment *fragment)
{
    // TODO save game
}

void UBasicRemenber::LoadMemory_Implementation()
{
    // TODO load game
}

bool UBasicRemenber::Share_Implementation(const FString& memoryID, const TScriptInterface<IRemember> &target)
{
    bool result = false;
    if (Contains_Implementation(memoryID) && target.GetObject() != nullptr)
    {
        // Get memory
        UMemoryFragment *memoryFragment = NewObject<UMemoryFragment>();
        GetMemory(memoryID, memoryFragment);

        // Send
        target->Accept(memoryID, memoryFragment);
        result = true;
    }

    return result;
}

void UBasicRemenber::Accept_Implementation(const FString& memoryID, const UMemoryFragment* inMemory)
{
    UMemoryFragment* memory = const_cast<UMemoryFragment*>(inMemory);
    m_Memory->fragments.Add(memory);
}

bool UBasicRemenber::RemoveMemory_Implementation(const FString& memoryID)
{
    bool result = false;
    if (Contains_Implementation(memoryID))
    {
        m_Memory->fragments.RemoveAll([=](const UMemoryFragment *memory) { return memoryID == memory->thingType; });
        result = true;
    }

    return result;
}

void UBasicRemenber::Clean_Implementation()
{
    m_Memory->Clean();
}

void UBasicRemenber::SortMemory_Implementation()
{
    if (m_Memory->fragments.Num() <= 1)
    {
        return;
    }

    m_Memory->fragments.Sort([](const UMemoryFragment &fragA, const UMemoryFragment &fragB) {
        if (fragA.memoryState == EMemoryState::Memory_Creating && fragB.memoryState != EMemoryState::Memory_Creating)
        {
            return true;
        }
        else if (fragA.memoryState > EMemoryState::Memory_Creating && fragB.memoryState <= EMemoryState::Memory_Creating)
        {
            return false;
        }

        return true;
    });
}

int UBasicRemenber::GetFirstMemory_Implementation(UMemoryFragment *outMemory, bool createNew = true)
{
    int index = -1;
    SortMemory_Implementation();
    bool hasUnfinished = m_Memory->fragments.ContainsByPredicate([](UMemoryFragment *frag) {
        return frag->memoryState == EMemoryState::Memory_Creating || frag->memoryState == EMemoryState::Memory_Creating;
    });

    if (hasUnfinished)
    {
        index = 0;
        outMemory = m_Memory->fragments[0];
    }
    else if (createNew)
    {
        index = 0;
        UMemoryFragment *fragment = NewObject<UMemoryFragment>();
        m_Memory->fragments.Insert(fragment, 0);
        outMemory = m_Memory->fragments[0];
    }

    return index;
}
