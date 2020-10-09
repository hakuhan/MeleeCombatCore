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
    TArray<AActor *> m_HittedActors;

protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
    TArray<UObject *> m_HitEffects;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
    TArray<UObject *> m_CombatEffects;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MustImplement = "HitEffect"), Category = "Effect")
    TArray<TSubclassOf<UObject>> m_HitEffectClasses;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MustImplement = "CombatingEffect"), Category = "Effect")
    TArray<TSubclassOf<UObject>> m_CombatingClasses;

public:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Effect")
    void HitEffect(FHitResult hitInfo);
    UFUNCTION(BlueprintCallable, Category = "Effect")
    void ShowCombatingEffect();
    UFUNCTION(BlueprintCallable, Category = "Effect")
    void StopCombatingEffect();
    UFUNCTION(BlueprintCallable, Category = "Effect")
    void ResetData();

#pragma region ManageEffect
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Effect")
    void InitEffects();

    UFUNCTION(BlueprintCallable, Category = "Effect")
    void InitFromOwner();

    UFUNCTION(BlueprintCallable, Category = "Effect")
    void InitFromComponents();
    
    // Init by classes link
    UFUNCTION(BlueprintCallable, Category = "Effect")
    void InitEffectClasses();

    UFUNCTION(BlueprintCallable, Category = "Effect")
    void AddHitEffect(UObject* effect);

    UFUNCTION(BlueprintCallable, Category = "Effect")
    void AddCombatingEffect(UObject* effect);

    UFUNCTION(BlueprintCallable, Category = "Effect")
    void RemoveHitEffect(UObject* effect);

    UFUNCTION(BlueprintCallable, Category = "Effect")
    void RemoveCombatingEffect(UObject* effect);

#pragma endregion ManageEffect


protected:
    // check array's element is valid
    void CheckEffectClass(TArray<UObject *>& arrays);
    UFUNCTION(BlueprintCallable)

    void AddInterfaceFromComponents(TSubclassOf<UInterface> Interface, TArray<UObject *> &array);
};
