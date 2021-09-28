// Fill out your copyright notice in the Description page of Project Settings.

#include "RemoteDetection/DetectRemote.h"

// Sets default values for this component's properties
UDetectRemote::UDetectRemote()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDetectRemote::Launch(const FDetectRemoteInfo &info)
{
	// Create detector
	if (info.DetectorClass)
	{
		UObject *detectorObj = NewObject<UObject>(this, info.DetectorClass);
		if (detectorObj)
		{
			IRemoteDetector *detectInterface = dynamic_cast<IRemoteDetector *>(detectorObj);
			
			// Bind detector callback
			if (detectInterface)
			{
				FOnRemoteHit hitEvent;
				hitEvent.BindUObject(this, &UDetectRemote::OnHit);
				detectInterface->BindHitEvent(hitEvent);
				IRemoteDetector::Execute_StartDetection(detectorObj);
			}
			
		}

		switch (info.Type)
		{
		case ERemoteDetector::ATTACH_DETECTOR:
			if (info.AttachTarget)
			{
				UActorComponent* detectorComp = dynamic_cast<UActorComponent*>(detectorObj);
				if (detectorComp)
				{
					info.AttachTarget->AddOwnedComponent(detectorComp);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Attack actor is not valid!"))
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Attack actor is not valid!"))
			}
			
			break;

		default:
			break;
		}
	}

}

// Called every frame
void UDetectRemote::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDetectRemote::OnHit(const FDetectInfo &info)
{
	// Compute hit
}