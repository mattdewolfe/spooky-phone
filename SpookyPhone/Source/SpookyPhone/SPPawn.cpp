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
	float xMovement = 0;
	float yMovement = 0;
	// If the difference is less than precision, player is moving straight
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, "movement added");
	yMovement = leftWheelMotion + rightWheelMotion;
	xMovement = rightWheelMotion - (leftWheelMotion / 2);
	FRotator tempRot = GetControlRotation();
	tempRot.Add(0, 0, xMovement);
	FVector newDirection = GetControlRotation().Vector();

	GetCharacterMovement()->AddInputVector(newDirection * leftWheelMotion + rightWheelMotion);
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





