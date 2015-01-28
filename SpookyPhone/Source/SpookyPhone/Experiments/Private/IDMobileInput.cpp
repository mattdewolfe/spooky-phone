// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeVariant.h"
#include "IDMobileInput.h"
#include "Engine.h"

UIDMobileInput::UIDMobileInput(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer)
{
	touchX = 0;
	touchY = 0;
	lastTouchX = 0;
	lastTouchY = 0;
}

bool UIDMobileInput::InputTouch(uint32 _Handle, ETouchType::Type _Type, const FVector2D& _TouchLocation, FDateTime _DeviceTimestamp, uint32 _TouchpadIndex)
{
	UPlayerInput::InputTouch(_Handle, _Type, _TouchLocation, _DeviceTimestamp, _TouchpadIndex);
	switch (_Type)
	{
	case ETouchType::Began:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Touch: Began"));
		break;

	case ETouchType::Moved:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Touch: Moved"));
		break;

	case ETouchType::Stationary:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Touch: Stationary"));
		break;

	case ETouchType::Ended:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Touch: Ended"));
		break;

	}
	return true;
}





