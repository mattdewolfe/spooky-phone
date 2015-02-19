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
	//CalculateAndApplyMovement();
}

// First attempt at tank controls for wheelchair.
// This is garbage at the moment, and does not factor in new
// Rift view rotation code
void ASPPawn::CalculateAndApplyMovement()
{
	FVector newDirection = GetControlRotation().Vector();
	bool bLeftWheelMovement = false;
	bool bRightWheelMovement = false;
	float tempScale = 0.0f;
	if (leftWheelMotion != 0.0f)
	{
		tempScale += leftWheelMotion;
		bLeftWheelMovement = true;
	}
	if (rightWheelMotion != 0.0f)
	{
		tempScale += rightWheelMotion;
		bRightWheelMovement = true;
	}
	if (bLeftWheelMovement && bRightWheelMovement)
	{
		//	newDirection *= tempScale;
		AddMovementInput(newDirection, tempScale);
	}
	// Consider rotation movement and clamp to 1.0f
	if (bRightWheelMovement || bLeftWheelMovement)
	{
		AddControllerYawInput((leftWheelMotion + rightWheelMotion)*0.1);
	}

}

void ASPPawn::SetupPlayerInputComponent(UInputComponent * _InputComponent)
{
	_InputComponent->BindAxis("MoveForward", this, &ASPPawn::LeftWheelMovement);
	_InputComponent->BindAxis("Turn", this, &ASPPawn::RightWheelMovement);
}

void ASPPawn::LeftWheelMovement(float _value)
{
	AddMovementInput(GetControlRotation().Vector(), _value);
}

void ASPPawn::RightWheelMovement(float _value)
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
