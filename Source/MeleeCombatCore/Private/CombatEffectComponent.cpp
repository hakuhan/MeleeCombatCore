#include "CombatEffectComponent.h"

// void UCombatEffectComponent::BeginPlay()
// {
//     UpdateEffects();
// }

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

void UCombatEffectComponent::CheckEffectClass(TArray<UObject *>& arrays)
{
    for (int i = arrays.Num() - 1; i >= 0; --i)
    {
        if (!arrays[i])
        {
            arrays.RemoveAt(i);
        }
    }
}

// void UCombatEffectComponent::UpdateEffects()
// {
//     for (auto hitClass : m_HitEffectClasses)
//     {
//         if (hitClass)
//         {
//             m_HitEffects.Add(NewObject<UObject>(this, hitClass));
//         }
//     }

//     for (auto combatingClass : m_CombatingClasses)
//     {
//         if (combatingClass)
//         {
//             m_CombatEffects.Add(NewObject<UObject>(this, combatingClass));
//         }
//     }
// }