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

	PhoneClass = ASpookyPawn::StaticClass();
	ConstructorHelpers::FObjectFinder<UBlueprint> PhoneBlueprint(TEXT("Blueprint'/Game/Blueprints/BP_SpookyPhone.BP_SpookyPhone'"));
	if (PhoneBlueprint.Object != NULL)
	{
		PhoneClass = (UClass*)PhoneBlueprint.Object->GeneratedClass;
	}
}

void ASpookyPawn::BeginPlay()
{
	Super::BeginPlay();

	// get a reference to the world
	UWorld* world = GetWorld();

	if (world)
	{
		// spawn the phone near the pawn
		Phone = GetWorld()->SpawnActor<ASpookyPhoneActor>(PhoneClass, FVector(50.f, 0.f, 50.f), FRotator(0.f, 90.f, 90.f));
		Phone->AttachRootComponentToActor(this, NAME_None, EAttachLocation::KeepRelativeOffset);
	}
}

void ASpookyPawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// bind some simple input
	InputComponent->BindAxis("Forward", this, &ASpookyPawn::OnForward);
	InputComponent->BindAction("E", IE_Pressed, this, &ASpookyPawn::OnEPressed);
	InputComponent->BindAction("D", IE_Pressed, this, &ASpookyPawn::OnDPressed);
}

void ASpookyPawn::OnEPressed()
{
	Phone->TogglePhone();
}

void ASpookyPawn::OnDPressed()
{
	Phone->TogglePhoneUI();
}

void ASpookyPawn::OnForward(float value)
{
	MovementComponent->AddInputVector(GetActorForwardVector() * value);
}