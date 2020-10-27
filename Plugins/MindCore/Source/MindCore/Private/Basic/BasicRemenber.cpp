#include "Basic/BasicRemenber.h"

UBasicRemenber::UBasicRemenber()
{
    m_CurrentIndex = -1;
}

UBasicRemenber::~UBasicRemenber()
{
}

void UBasicRemenber::GetAllWishes_Implementation(TArray<FWishThing> &outWishes)
{
    outWishes.Empty();

    for (auto memory : m_Memory.fragments)
    {
        outWishes.Add(memory.wishData);
    }
}

void UBasicRemenber::CurrentMemory_Implementation(FMemoryFragment &outFragment)
{
    if (m_CurrentIndex == -1 || m_Memory.fragments.Num() == 0)
    {
        CreateMemory_Implementation(outFragment);
        m_CurrentIndex = 0;
        return;
    }

    if (m_CurrentIndex >= m_Memory.fragments.Num() || m_CurrentIndex < 0)
    {
        m_CurrentIndex = GetFirstMemory_Implementation(outFragment, true);
    }
}

bool UBasicRemenber::Conatins_Implementation(FString memoryID)
{
    bool result = false;

    result = m_Memory.fragments.ContainsByPredicate([=](const FMemoryFragment &memory) {
        return memory.thingType == memoryID;
    });

    return result;
}

void UBasicRemenber::CreateMemory_Implementation(FMemoryFragment &outMemory)
{
    FMemoryFragment fragment;
    m_Memory.fragments.Add(fragment);
    outMemory = outMemory;
}

void UBasicRemenber::GetMemory_Implementation(FString memoryID, FMemoryFragment &outMemory)
{
    for (auto fragment : m_Memory.fragments)
    {
        if (fragment.thingType == memoryID)
        {
            outMemory = fragment;
            break;
        }
    }
}

void UBasicRemenber::Store_Implementation(const FMemoryFragment &fragment)
{
    // TODO save game
}

bool UBasicRemenber::Share_Implementation(FString memoryID, const TScriptInterface<IRemember> &target)
{
    bool result = false;
    if (Conatins_Implementation(memoryID) && target.GetObject() != nullptr)
    {
        // Get memory
        FMemoryFragment memoryFragment;
        GetMemory_Implementation(memoryID, memoryFragment);

        // Send
        IRemember::Execute_Accept(target.GetObject(), memoryID, memoryFragment);
        result = true;
    }

    return result;
}

void UBasicRemenber::Accept_Implementation(FString memoryID, FMemoryFragment &inMemory)
{
    m_Memory.fragments.Add(inMemory);
}

bool UBasicRemenber::RemoveMemory_Implementation(FString memoryID)
{
    bool result = false;
    if (Conatins_Implementation(memoryID))
    {
        m_Memory.fragments.RemoveAll([=](const FMemoryFragment &memory) { return memoryID == memory.thingType; });
        result = true;
    }

    return result;
}

void UBasicRemenber::Clean_Implementation()
{
    m_Memory.Clean();
}

void UBasicRemenber::SortMemory_Implementation()
{
    if (m_Memory.fragments.Num() <= 1)
    {
        return;
    }

    m_Memory.fragments.Sort([](const FMemoryFragment &fragA, const FMemoryFragment &fragB) {
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

int UBasicRemenber::GetFirstMemory_Implementation(FMemoryFragment &outMemory, bool createNew = true)
{
    int index = -1;
    SortMemory_Implementation();
    bool hasUnfinished = m_Memory.fragments.ContainsByPredicate([](const FMemoryFragment &frag) {
        return frag.memoryState == EMemoryState::Memory_Creating || frag.memoryState == EMemoryState::Memory_Creating;
    });

    if (hasUnfinished)
    {
        index = 0;
        outMemory = m_Memory.fragments[0];
    }
    else if (createNew)
    {
        index = 0;
        FMemoryFragment fragment;
        m_Memory.fragments.Insert(fragment, 0);
        outMemory = m_Memory.fragments[0];
    }

    return index;
}
