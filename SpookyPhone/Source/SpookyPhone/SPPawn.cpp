// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SPPawn.h"
#include "SPPlayerController.h"

ASPPawn::ASPPawn(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer)
{
	ColliderComponent = _ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("ColliderComponent"));
	ColliderComponent->SetCapsuleSize(5.0f, 5.0f);
	RootComponent = ColliderComponent;

	MovementComponent = _ObjectInitializer.CreateDefaultSubobject<UFloatingPawnMovement>(this, TEXT("MovementComponent"));

	PrimaryActorTick.bCanEverTick = true;
	wheelMotionPrecision = 0.2f;
}

void ASPPawn::Tick(float _DeltaTime)
{
	CalculateAndApplyMovement();
}

// First attempt at tank controls for wheelchair.
// This is garbage at the moment, and does not factor in new
// Rift view rotation code
void ASPPawn::CalculateAndApplyMovement()
{
	// For the time being, we are multiplaying input values by magical floats in 
	// order to slow down the speed of rotation and movement

	// If left wheel is not moving, and right is
	if (abs(leftWheelMotion) <= 0.1f && rightWheelMotion != 0.0f)
	{
		// Add rights negative yaw motion
		AddControllerYawInput(rightWheelMotion*0.25);
	}
	// If left wheel is moving and right is not
	else if (leftWheelMotion != 0.0f && abs(rightWheelMotion) <= 0.1f)
	{
		// Add lefts yaw motion
		AddControllerYawInput(leftWheelMotion*0.25);
	}
	// If both are non zero, combine for yaw and movement
	else if (abs(rightWheelMotion) >= 0.1f && abs(leftWheelMotion) >= 0.1f)
	{
		AddControllerYawInput((leftWheelMotion + rightWheelMotion)*0.2);
		AddMovementInput(GetControlRotation().Vector(), (leftWheelMotion - rightWheelMotion)*0.5);
	}
}

void ASPPawn::SetupPlayerInputComponent(UInputComponent * _InputComponent)
{
// Normal fps setup
//	_InputComponent->BindAxis("MoveForward", this, &ASPPawn::MoveForward);
//	_InputComponent->BindAxis("Turn", this, &ASPPawn::Turn);
	_InputComponent->BindAxis("LeftWheel", this, &ASPPawn::LeftWheelMoved);
	_InputComponent->BindAxis("RightWheel", this, &ASPPawn::RightWheelMoved);
}

void ASPPawn::LeftWheelMoved(float _value)
{
	leftWheelMotion = _value;
}

void ASPPawn::RightWheelMoved(float _value)
{
	rightWheelMotion = _value;
}

void ASPPawn::MoveForward(float _value)
{
	AddMovementInput(GetControlRotation().Vector(), _value);
}

void ASPPawn::Turn(float _value)
{
	AddControllerYawInput(_value);
}

// Get our view rotation (from controller)
FRotator ASPPawn::GetViewRotation() const
{
	if (ASPPlayerController* MYPC = Cast<ASPPlayerController>(Controller))
	{
		return MYPC->GetViewRotation();
	}
	return GetActorRotation();
}
