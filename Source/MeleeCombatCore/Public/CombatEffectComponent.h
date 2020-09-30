/*
    Author: baihan 
    class purpose: Manage effect of combat 
*/

#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"
#include "HitEffect.h"
#include "CombatingEffect.h"
#include "CombatEffectComponent.generated.h"

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class MELEECOMBATCORE_API UCombatEffectComponent : public UActorComponent
{
    GENERATED_BODY()
private:
    TArray<AActor*> m_HittedActors;

    // Effects
    TArray<UObject*> m_HitEffects;
    TArray<UObject*> m_CombatEffects;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MustImplement = "HitEffect"))
    TArray<TSubclassOf<UObject>> m_HitEffectClasses;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MustImplement = "CombatingEffect"))
    TArray<TSubclassOf<UObject>> m_CombatingClasses;

public:
	virtual void BeginPlay() override;


    UFUNCTION(BlueprintCallable)
    void HitEffect(FHitResult hitInfo);
    UFUNCTION(BlueprintCallable)
    void ShowCombatingEffect();
    UFUNCTION(BlueprintCallable)
    void StopCombatingEffect();
    UFUNCTION(BlueprintCallable)
    void ResetData();
    UFUNCTION(BlueprintCallable)
    void UpdateEffects();

protected:
    // check array's element is valid
    void CheckEffectClass(TArray<UObject*> arrays);
};