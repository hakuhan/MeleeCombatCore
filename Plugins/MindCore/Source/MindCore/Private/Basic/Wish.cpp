#include "Basic/Wish.h"

void UWish::Init(const FWishInfo &Info)
{
	m_Info = Info;

	Reset();
}

void UWish::UpdateWish_Implementation()
{
	if (m_Data.SeekingWishes.Num() == 0)
	{
		return;
	}
	
	for (int i = m_Data.SeekingWishes.Num() - 1; i >= 0; --i)
	{
		bool wishOver = false;
		int index = m_Data.OwnedThings.IndexOfByPredicate([&](const FThing &target) { return target.Name == m_Data.SeekingWishes[i].Name; });
		if (index >= 0)
		{
			if (!m_Data.OwnedThings[index].NeverEnding && m_Data.OwnedThings[index].Number >= m_Data.SeekingWishes[i].Number)
			{
				wishOver = true;
			}
			else if (m_Data.OwnedThings[index].NeverEnding && m_Data.OwnedThings[index].Disappearance)
			{
				wishOver = true;
			}
		}
		else if (m_Data.SeekingWishes[i].Disappearance)
		{
			wishOver = true;
		}

		if (wishOver)
		{
			if (index < 0)
			{
				m_Data.OwnedThings.Add(m_Data.SeekingWishes[i]);
			}
			m_Data.SeekingWishes.RemoveAt(i);
		}
	}
}

bool UWish::CreateWish_Implementation(const FThing &wish)
{
	int index = m_Info.Wishes.IndexOfByPredicate([&](const FThing &target) { return wish.Name == target.Name; });
	if (index < 0)
	{
		m_Info.Wishes.Add(wish);
	}
	else
	{
		m_Info.Wishes[index].Number += wish.Number;
	}

	return true;
}

bool UWish::ObtainThing_Implementation(const FThing &thing)
{
	int index = m_Data.OwnedThings.IndexOfByPredicate([&](const FThing &target) { return target.Name == thing.Name; });
	if (index < 0)
	{
		m_Data.OwnedThings.Add(thing);
	}
	else
	{
		m_Data.OwnedThings[index].Number += thing.Number;
	}

	return true;
}

bool UWish::LoseWish_Implementation(const FString &wishName)
{
	return m_Data.SeekingWishes.RemoveAll([&](const FThing &target) { return target.Name == wishName; }) > 0;
}

bool UWish::LoseThing_Implementation(const FString &thingName)
{
	return m_Data.OwnedThings.RemoveAll([&](const FThing &target) { return target.Name == thingName; }) > 0;
}

void UWish::Reset_Implementation()
{
	m_Data.SeekingWishes = m_Info.Wishes;
	m_Data.OwnedThings.Empty();
}