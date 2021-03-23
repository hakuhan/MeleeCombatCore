#include "Basic/Wish.h"

void UWish::DoWish_Implementation()
{
    
}

void UWish::CreateWish_Implementation(UThing* wish)
{
    if (!m_Info->Wishes.Find(wish))
    {
        m_Info->Wishes.Add(wish);
    }
}

void UWish::UpdateWish_Implementation(const FString& originName, UThing* newWish)
{
    if (newWish == nullptr)
    {
        return;
    }

    int targetIndex = m_Info->Wishes.IndexOfByPredicate([&](UThing* thing){
        return thing->Name == originName;
    });

    if (targetIndex >= 0)
    {
        m_Info->Wishes[targetIndex] = newWish;
    }
}