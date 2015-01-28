// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerInput.h"
#include "IDMobileInput.generated.h"

/**
 * 
 */
UCLASS()
class CODEVARIANT_API UIDMobileInput : public UPlayerInput
{
	GENERATED_UCLASS_BODY()
private:
	float touchX;
	float touchY;
	float lastTouchX;
	float lastTouchY;
	
public:
	// Override touch input event
	virtual bool InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex);
	
};
