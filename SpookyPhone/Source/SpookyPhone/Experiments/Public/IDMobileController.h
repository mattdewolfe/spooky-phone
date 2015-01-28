// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "IDMobileController.generated.h"

/**
 * 
 */
UCLASS()
class CODEVARIANT_API AIDMobileController : public APlayerController
{
	GENERATED_UCLASS_BODY()

protected:
	// Stores the movement values for the pawn to act on
	float xMovement;
	float yMovement;
	// Store current x/y position of touch
	float xPos;
	float yPos;
	// Store starting positions of x and y 
	float startX;
	float startY;
	// The distance we need to move on either axis to recognize it as the
	// intended direction of movement
	float minimumRecognizedSwipeDistance;
	// Track if touch as just released
	// !! Critical to current system that this is only set back to true when
	// CurrenltyPressed (inside the gettouchstate function) returns false
	bool wasReleased;
	// Track if touch is currently being pressed
	bool isCurrentlyPressed;
	// Flags set for different movement directions
	bool isHorizontalSwipe;
	bool isVerticalSwipe;

public:
	// Overrides for engine functions
	virtual void GetInputTouchState(ETouchIndex::Type _FingerIndex, float& _LocationX, float& _LocationY, bool& _bIsCurrentlyPressed);
	virtual void Tick(float _DeltaTime);

	float const GetXMovement() { return xMovement; }
	float const GetYMovement() { return yMovement; }
private:
	/* Called by GetInputTouchState, if input position (x or y) is changing fast enough
	** @Parem, float: Set Movement axis to this value, unless passed in with decrement flag
	** @Parem, bool: Optional flag to multiply Movement value by _value parem
	** Function used to either set movement value or multiply it by a % -MD */
	void OnSwipeLeftRight(float _value, bool _multiply = false);
	void OnSwipeUpDown(float _value, bool _multiply = false);
	
	// Called by timer to halt movement from swipe
	void SwipeMovementTimeout();
};
