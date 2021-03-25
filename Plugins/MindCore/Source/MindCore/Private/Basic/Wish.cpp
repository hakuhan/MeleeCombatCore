#include "Basic/Wish.h"

void UWish::Init(UWishInfo *Info)
{
	m_Info = Info;
	m_Data = FWishData();

	Reset();
}

void UWish::UpdateWish_Implementation()
{
	if (m_Data.SeekingWishes.Num() == 0)
	{
		return;
	}
	
	m_Data.SeekingWishes.RemoveAll([](UThing *target) { return nullptr == target; });
	m_Data.OwnedThings.RemoveAll([](UThing *target) { return nullptr == target; });
	for (int i = m_Data.SeekingWishes.Num() - 1; i <= 0; --i)
	{
		int index = m_Data.OwnedThings.IndexOfByPredicate([&](UThing *target) { return target->Name == m_Data.SeekingWishes[i]->Name; });
		if (index >= 0 && m_Data.OwnedThings[index]->Number >= m_Data.SeekingWishes[i]->Number)
		{
			m_Data.OwnedThings.Add(m_Data.SeekingWishes[i]);
			m_Data.SeekingWishes.RemoveAt(i);
		}
	}
}

bool UWish::CreateWish_Implementation(UThing *wish)
{
	if (wish == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Wish you added is empty"))
		return false;
	}

	int index = m_Info->Wishes.IndexOfByPredicate([&](UThing *target) { return wish->Name == target->Name; });
	if (index < 0)
	{
		m_Info->Wishes.Add(wish);
	}
	else
	{
		m_Info->Wishes[index]->Number += wish->Number;
	}

	return true;
}

bool UWish::ObtainThing_Implementation(UThing *thing)
{
	if (thing == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Wish you added is empty"))
		return false;
	}

	int index = m_Data.OwnedThings.IndexOfByPredicate([&](UThing *target) { return target->Name == thing->Name; });
	if (index < 0)
	{
		m_Data.OwnedThings.Add(thing);
	}
	else
	{
		m_Data.OwnedThings[index]->Number += thing->Number;
	}

	return true;
}

bool UWish::LoseWish_Implementation(const FString &wishName)
{
	return m_Data.SeekingWishes.RemoveAll([&](UThing *target) { return target->Name == wishName; }) > 0;
}

bool UWish::LoseThing_Implementation(const FString &thingName)
{
	return m_Data.OwnedThings.RemoveAll([&](UThing *target) { return target->Name == thingName; }) > 0;
}

void UWish::Reset_Implementation()
{
	if (m_Info != nullptr)
	{
		m_Data.SeekingWishes = m_Info->Wishes;
	}
}