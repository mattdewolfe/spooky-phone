// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeVariant.h"
#include "IDMobileCharacter.h"
#include "IDMobileController.h"
#include "Engine.h"


AIDMobileCharacter::AIDMobileCharacter(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer)
{
	distanceFromCentre = 3000.0f;
	bIsViewingExterior = false;
	bIsTouchPressed = false;
	startXPosition = 0;
	startYPosition = 0;
	xMovementValue = 0;
	yMovementValue = 0;
	PrimaryActorTick.bCanEverTick;
}

void AIDMobileCharacter::Tick(float _DeltaSeconds)
{
	Super::Tick(_DeltaSeconds);
	MovePawn();
}

void AIDMobileCharacter::MovePawn()
{
	AIDMobileController* tempC = Cast<AIDMobileController>(Controller);
	// Get movement values from controller and pass into pawn
	AddControllerYawInput(tempC->GetXMovement());
	AddMovementInput(GetActorForwardVector(), tempC->GetYMovement());
}

void AIDMobileCharacter::TransferPosition()
{}

void AIDMobileCharacter::OrbitOrigin()
{}



