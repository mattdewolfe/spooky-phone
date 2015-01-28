// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeVariant.h"
#include "IDMobileController.h"
#include "Engine.h"

AIDMobileController::AIDMobileController(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer)
{
	xMovement = 0;
	yMovement = 0;
	xPos = 0;
	yPos = 0;
	minimumRecognizedSwipeDistance = 200.f;
	wasReleased = true;
	isCurrentlyPressed = false;
	isHorizontalSwipe = false;
	isVerticalSwipe = false;
	PrimaryActorTick.bCanEverTick;
	
}

/* Call the GetInputTouchState inherited from parent, this will update our x and y positions with the floats passed in
** After wards, we do our own calculations on touch positions versus previous touch positions to determine swipe
** direction of finger -MD */
void AIDMobileController::GetInputTouchState(ETouchIndex::Type _FingerIndex, float& _LocationX, float& _LocationY, bool& _bIsCurrentlyPressed)
{
	APlayerController::GetInputTouchState(_FingerIndex, _LocationX, _LocationY, _bIsCurrentlyPressed);

	if (_bIsCurrentlyPressed == true)
	{
		// If this is still true than this is the initial touch position, store it for calculations on direction
		if (wasReleased == true)
		{
			startX = _LocationX;
			startY = _LocationY;
			isVerticalSwipe = false;
			isHorizontalSwipe = false;
		}
		/* After the first touch position is set we do calculations on direction of 
		** the swipe. If either swipe direction flag is set to true than we have
		** decided on a direction and can avoid all of these calculations - MD */
		else if (isHorizontalSwipe == false && isVerticalSwipe == false)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Touch update."));
			// Calculate absolute values for movement on each axis
			float absX = abs(startX - _LocationX);
			float absY = abs(startY - _LocationY);
			// Check if we have moved far enough along X for horizontal swipe
			if (absX > minimumRecognizedSwipeDistance)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Horizontal Swipe"), _LocationX));
				// Calculate value to pass into swipe movement function
				isHorizontalSwipe = true;
				float inVal = ((_LocationX - startX) / absX)/1.5f;
				GetWorldTimerManager().SetTimer(this, &AIDMobileController::SwipeMovementTimeout, 0.5f, false);
				OnSwipeLeftRight(inVal);
			}
			// Check if we have moved far enough on Y for vertical swipe
			else if (absY > minimumRecognizedSwipeDistance)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Y: %f - changed"), _LocationY));
				// Calculate value to pass into swipe movement function
				isVerticalSwipe = true;
				float inVal = (startY - _LocationY) / absY;
				GetWorldTimerManager().SetTimer(this, &AIDMobileController::SwipeMovementTimeout, 0.5f, false);
				OnSwipeUpDown(inVal);
			}
		}
		// Set our release flag to false
		wasReleased = false;
	}

	/* If our release flag is false, but touch is not pressed
	** we can set our was released flag to true -MD */
	else if (wasReleased == false)
	{
		wasReleased = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Was Released Flag"), _LocationY));	
	}
}

void AIDMobileController::Tick(float _DeltaSeconds)
{
	Super::Tick(_DeltaSeconds);
	GetInputTouchState(ETouchIndex::Touch1, xPos, yPos, isCurrentlyPressed);
}

// Set or multiply X movement value
void AIDMobileController::OnSwipeLeftRight(float _value, bool _multiply)
{
	if (_multiply)
	{
		xMovement *= _value;
	}
	else
	{
		xMovement = _value;
	}
}

// Set or multiply Y movement value
void AIDMobileController::OnSwipeUpDown(float _value, bool _multiply)
{
	if (_multiply)
	{
		yMovement *= _value;
	}
	else
	{
		yMovement = _value;
	}
}

void AIDMobileController::SwipeMovementTimeout()
{
	yMovement = 0.0f;
	xMovement = 0.0f;
	isVerticalSwipe = true;
	isHorizontalSwipe = true;
}

