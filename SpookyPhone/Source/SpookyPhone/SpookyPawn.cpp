// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SpookyPawn.h"

ASpookyPawn::ASpookyPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ColliderComponent = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("ColliderComponent"));
	ColliderComponent->SetCapsuleSize(5.f, 5.f);
	ColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = ColliderComponent;

	MovementComponent = ObjectInitializer.CreateDefaultSubobject<UFloatingPawnMovement>(this, TEXT("MovementComponent"));
}

void ASpookyPawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("Forward", this, &ASpookyPawn::OnForward);
}

void ASpookyPawn::OnForward(float value)
{
	MovementComponent->AddInputVector(GetActorForwardVector() * value);
}