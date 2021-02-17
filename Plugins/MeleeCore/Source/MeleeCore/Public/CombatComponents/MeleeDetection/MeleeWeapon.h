/*
	Author: baihan 
	class purpose: Mark Melee weapon 
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MeleeDetection/MeleeWeaponInfo.h"
#include "MeleeWeapon.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MeleeWeapon)
	TArray<FVector> TempSocketLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MeleeWeapon)
	bool IsEnabled = true;
public:
	FWeaponData() 
	{
		IsEnabled = true;
	}
	FWeaponData(bool isEnabled) 
	{
		IsEnabled = isEnabled;
	}
	~FWeaponData()
	{
		TempSocketLocation.Empty();
	}
};

UINTERFACE()
class MELEECORE_API UMeleeWeapon : public UInterface
{
	GENERATED_BODY()
};

class MELEECORE_API IMeleeWeapon
{
	GENERATED_BODY()

public:
	virtual bool GetInfo(FMeleeWeaponInfo& outInfo) = 0;
	virtual bool GetData(FWeaponData& outData) = 0;
	virtual void SetData(const FWeaponData& inData) = 0;
	virtual bool IsWeaponEnabled()
	{
		return true;
	}
	virtual void SetWeaponEnabled(bool enable) = 0;

	virtual FVector GetDetectLocation(FName SocketName) = 0;
	bool IsTargetWeapon(uint8 WeaponMask)
	{
		bool result = false;

		FMeleeWeaponInfo _info; 
		result = GetInfo(_info);
		if (result)
		{
			result = _info.WeaponType & WeaponMask;
		}
		
		return result;
	}
};

UCLASS(ClassGroup = (MeleeCore), meta = (BlueprintSpawnableComponent))
class MELEECORE_API USimpleWeapon : public UStaticMeshComponent, public IMeleeWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMeleeWeaponInfo m_Info;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponData m_Data;

protected:
	USimpleWeapon();

	virtual void BeginPlay() override;
	virtual FVector GetDetectLocation(FName SocketName) override
	{
		return GetSocketLocation(SocketName);
	}
	virtual bool GetInfo(FMeleeWeaponInfo& outInfo) override
	{
		outInfo = m_Info;
		return true; 
	}

	virtual bool GetData(FWeaponData& outData) override
	{
		outData = m_Data;
		return true;
	}
	virtual void SetData(const FWeaponData& inData) override
	{
		m_Data = inData;
	}
	virtual bool IsWeaponEnabled() override
	{
		return m_Data.IsEnabled;
	}
	virtual void SetWeaponEnabled(bool enable) override
	{
		m_Data.IsEnabled = enable;
	}
};

UCLASS(ClassGroup = (MeleeCore), meta = (BlueprintSpawnableComponent))
class MELEECORE_API USkeletalWeapon : public USkeletalMeshComponent, public IMeleeWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMeleeWeaponInfo m_Info;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponData m_Data;

protected:
	USkeletalWeapon();
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual FVector GetDetectLocation(FName SocketName) override
	{
		return GetSocketLocation(SocketName);
	}
	virtual bool GetInfo(FMeleeWeaponInfo& outInfo) override
	{
		outInfo = m_Info;
		return true; 
	}

	virtual bool GetData(FWeaponData& outData) override
	{
		outData = m_Data;
		return true;
	}
	virtual void SetData(const FWeaponData& inData) override
	{
		m_Data = inData;
	}
	virtual bool IsWeaponEnabled() override
	{
		return m_Data.IsEnabled;
	}
	virtual void SetWeaponEnabled(bool enable) override
	{
		m_Data.IsEnabled = enable;
	}
};

UCLASS(ClassGroup = (MeleeCore), meta = (BlueprintSpawnableComponent))
class MELEECORE_API UInvisibleWeapon : public USceneComponent, public IMeleeWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName m_SocketName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMeleeWeaponInfo m_Info;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponData m_Data;

protected:
	UInvisibleWeapon();
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual FVector GetDetectLocation(FName SocketName) override
	{
		return GetComponentLocation();
	}
	virtual bool GetInfo(FMeleeWeaponInfo& outInfo) override
	{
		outInfo = m_Info;
		return true; 
	}

	virtual bool GetData(FWeaponData& outData) override
	{
		outData = m_Data;
		return true;
	}
	virtual void SetData(const FWeaponData& inData) override
	{
		m_Data = inData;
	}
	virtual bool IsWeaponEnabled() override
	{
		return m_Data.IsEnabled;
	}
	virtual void SetWeaponEnabled(bool enable) override
	{
		m_Data.IsEnabled = enable;
	}
};