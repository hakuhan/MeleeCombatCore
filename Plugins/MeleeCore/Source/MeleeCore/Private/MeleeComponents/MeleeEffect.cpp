// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeComponents/MeleeEffect.h"

// Sets default values for this component's properties
UMeleeEffect::UMeleeEffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UMeleeEffect::BeginPlay()
{
	Super::BeginPlay();

    InitEffects();
}

void UMeleeEffect::BeginDestroy()
{
	Super::BeginDestroy();

	m_HitEffects.Empty();
	m_HittedActors.Empty();
	m_HitEffectClasses.Empty();
}

void UMeleeEffect::OnCombatHitEffect(FHitResult hitInfo)
{
    CheckEffectClass(m_HitEffects);

    // check first effect
    auto actor = hitInfo.GetActor();
    if (!m_HittedActors.Contains(actor))
    {
        m_HittedActors.Add(actor);
        for (auto effect : m_HitEffects)
        {
            IMeleeHitEffect::Execute_OnMeleeFirstHitEffect(effect, hitInfo);
        }
        return;
    }

    for (auto effect : m_HitEffects)
    {
        IMeleeHitEffect::Execute_OnMeleeHitEffect(effect, hitInfo);
    }
}

void UMeleeEffect::CheckEffectClass(TArray<UObject *> &arrays)
{
    for (int i = arrays.Num() - 1; i >= 0; --i)
    {
        if (!arrays[i])
        {
            arrays.RemoveAt(i);
        }
    }
}

#pragma region ManageEffect

void UMeleeEffect::InitEffects_Implementation()
{
    // UE_LOG(LogTemp, Warning, TEXT("Init effect c++ "));
    InitFromOwner();

    InitFromComponents();

    InitEffectClasses();
}

void UMeleeEffect::InitFromOwner()
{
    auto owner = GetOwner();
    if (owner->GetClass()->ImplementsInterface(UMeleeHitEffect::StaticClass()))
    {
        m_HitEffects.Add(owner);
    }
}

void UMeleeEffect::InitFromComponents()
{
    UMeleeUtils::GetImplementFromActor(GetOwner() ,UMeleeHitEffect::StaticClass(), m_HitEffects, false);
}

void UMeleeEffect::InitEffectClasses()
{
    for (auto hitClass : m_HitEffectClasses)
    {
        if (hitClass)
        {
            m_HitEffects.Add(NewObject<UObject>(this, hitClass));
        }
    }
}

void UMeleeEffect::AddHitEffect(UObject *effect)
{
    if (effect && effect->GetClass()->ImplementsInterface(UMeleeHitEffect::StaticClass()))
    {
        m_HitEffects.Add(effect);
    }
}

void UMeleeEffect::RemoveHitEffect(UObject *effect)
{
    if (effect && m_HitEffects.Contains(effect))
    {
        m_HitEffects.Remove(effect);
    }
}

void UMeleeEffect::ResetData()
{
	m_HittedActors.Empty();
}

#pragma endregion ManageEffect
