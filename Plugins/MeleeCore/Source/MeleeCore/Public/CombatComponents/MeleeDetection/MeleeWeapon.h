// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeleeCoreStructures/MeleeStructure.h"
#include "Components/MeshComponent.h"
#include "MeleeDetection/MeleeWeaponInfo.h"
#include "MeleeWeapon.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MeleeWeapon)
	TArray<FVector> TempSocketLocation;

public:
	FWeaponData() {}
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

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MELEECORE_API USkeletalWeapon : public UStaticMeshComponent, public IMeleeWeapon
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
};
