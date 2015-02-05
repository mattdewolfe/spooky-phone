// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SPPawn.h"

ASPPawn::ASPPawn(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer)
{
	ColliderComponent = _ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("ColliderComponent"));
	ColliderComponent->SetCapsuleSize(5.0f, 5.0f);

	PrimaryActorTick.bCanEverTick = true;
	wheelMotionPrecision = 0.2f;
}

void ASPPawn::Tick(float _DeltaTime)
{
	CalculateAndApplyMovement();
}

void ASPPawn::CalculateAndApplyMovement()
{
	// If the difference is less than precision, player is moving straight
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, "movement added");

	// Get Control rotation then pass values into input
	AddControllerYawInput(leftWheelMotion/4);
	AddControllerYawInput(rightWheelMotion/4);
	
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
		newDirection *= tempScale;
		AddMovementInput(newDirection, tempScale);
	}
}

void ASPPawn::SetupPlayerInputComponent(UInputComponent * _InputComponent)
{
	_InputComponent->BindAxis("LeftWheel", this, &ASPPawn::LeftWheelMovement);
	_InputComponent->BindAxis("RightWheel", this, &ASPPawn::RightWheelMovement);
}

void ASPPawn::LeftWheelMovement(float _value)
{
	leftWheelMotion = _value;
}

void ASPPawn::RightWheelMovement(float _value)
{
	rightWheelMotion = _value;
}





