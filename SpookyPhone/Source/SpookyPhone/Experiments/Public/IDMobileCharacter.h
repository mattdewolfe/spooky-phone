// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "InputCoreTypes.h"
#include "IDMobileCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CODEVARIANT_API AIDMobileCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()
	
public:
	// Values used for calulating swipe direction/distance and assigning movement to the proper input axis
	// Starting X position of a touch
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TouchMovement)
	float startXPosition;

	// Starting Y position of a touch
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TouchMovement)
	float startYPosition; 

	// Movement rate along X
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TouchMovement)
	float xMovementValue;

	// Movement rate along Y
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TouchMovement)
	float yMovementValue;

	// Flag to track if player is currently viewing interior space or orbitting in external view
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TouchMovement)
	bool bIsViewingExterior;

	// Flag for tracking if touch state was down on last update loop
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TouchMovement)
	bool bIsTouchPressed;

	// Used for controlling distance from centre point when player is orbitting in external view
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TouchMovement)
	float distanceFromCentre;

	// Override tick event
	virtual void Tick(float _DeltaSeconds);

protected:

	// Move pawn based on XY movement calculations
	UFUNCTION()
	void MovePawn();

	UFUNCTION()
	void TransferPosition();

	UFUNCTION()
	void OrbitOrigin();

};
