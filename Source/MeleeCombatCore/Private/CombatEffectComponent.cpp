#include "CombatEffectComponent.h"

void UCombatEffectComponent::BeginPlay()
{
    InitEffects();
}

void UCombatEffectComponent::HitEffect(FHitResult hitInfo)
{
    CheckEffectClass(m_HitEffects);

    // check first effect
    auto actor = hitInfo.GetActor();
    if (!m_HittedActors.Contains(actor))
    {
        m_HittedActors.Add(actor);
        for (auto effect : m_HitEffects)
        {
            IHitEffect::Execute_FirstHitEffect(effect, hitInfo);
        }
    }

    for (auto effect : m_HitEffects)
    {
        IHitEffect::Execute_HitEffect(effect, hitInfo);
    }
}

void UCombatEffectComponent::ShowCombatingEffect()
{
    CheckEffectClass(m_CombatEffects);
    for (auto combatEft : m_CombatEffects)
    {
        ICombatingEffect::Execute_ShowCombatingEffect(combatEft);
    }
}

void UCombatEffectComponent::StopCombatingEffect()
{
    CheckEffectClass(m_CombatEffects);
    for (auto combatEft : m_CombatEffects)
    {
        ICombatingEffect::Execute_StopCombatingEffect(combatEft);
    }
}

void UCombatEffectComponent::ResetData()
{
    m_HittedActors.Empty();
}

void UCombatEffectComponent::CheckEffectClass(TArray<UObject *> &arrays)
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

void UCombatEffectComponent::InitEffects_Implementation()
{
    // UE_LOG(LogTemp, Warning, TEXT("Init effect c++ "));
    InitFromOwner();

    InitFromComponents();

    InitEffectClasses();
}

void UCombatEffectComponent::InitFromOwner()
{
    auto owner = GetOwner();
    if (owner->GetClass()->ImplementsInterface(UHitEffect::StaticClass()))
    {
        m_HitEffects.Add(owner);
    }
    if (owner->GetClass()->ImplementsInterface(UCombatingEffect::StaticClass()))
    {
        m_CombatEffects.Add(owner);
    }
}

void UCombatEffectComponent::InitFromComponents()
{
    AddInterfaceFromComponents(UHitEffect::StaticClass(), m_HitEffects);
    AddInterfaceFromComponents(UCombatingEffect::StaticClass(), m_CombatEffects);
}

void UCombatEffectComponent::AddInterfaceFromComponents(TSubclassOf<UInterface> Interface, TArray<UObject *> &array)
{
    auto comp = GetOwner()->GetComponentsByInterface(Interface);
    for (int i = 0; i < comp.Num(); ++i)
    {
        array.Add(comp[i]);
    }
}

void UCombatEffectComponent::InitEffectClasses()
{
    for (auto hitClass : m_HitEffectClasses)
    {
        if (hitClass)
        {
            m_HitEffects.Add(NewObject<UObject>(this, hitClass));
        }
    }

    for (auto combatingClass : m_CombatingClasses)
    {
        if (combatingClass)
        {
            m_CombatEffects.Add(NewObject<UObject>(this, combatingClass));
        }
    }
}

void UCombatEffectComponent::AddHitEffect(UObject *effect)
{
    if (effect && effect->GetClass()->ImplementsInterface(UHitEffect::StaticClass()))
    {
        m_HitEffects.Add(effect);
    }
}

void UCombatEffectComponent::AddCombatingEffect(UObject *effect)
{
    if (effect && effect->GetClass()->ImplementsInterface(UCombatingEffect::StaticClass()))
    {
        m_CombatEffects.Add(effect);
    }
}

void UCombatEffectComponent::RemoveHitEffect(UObject *effect)
{
    if (effect && m_HitEffects.Contains(effect))
    {
        m_HitEffects.Remove(effect);
    }
}

void UCombatEffectComponent::RemoveCombatingEffect(UObject *effect)
{
    if (effect && m_CombatEffects.Contains(effect))
    {
        m_CombatEffects.Remove(effect);
    }
}

#pragma endregion ManageEffect
