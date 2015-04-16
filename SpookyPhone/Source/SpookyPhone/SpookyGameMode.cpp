// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SpookyPlayerController.h"
#include "SpookyPawn.h"
#include "SpookyGameMode.h"

ASpookyGameMode::ASpookyGameMode(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer)
{
	// Init the standard version of our pawn
	UClass* MyPawnClass = ASpookyPawn::StaticClass();
	// Look for a predefined blueprint of our pawn
	ConstructorHelpers::FObjectFinder<UBlueprint> PawnBlueprint(TEXT("Blueprint'/Game/Blueprints/BP_SpookyPawn.BP_SpookyPawn'"));
	// If we find it, set the pawnclass to that
	if (PawnBlueprint.Object != NULL)
	{
		MyPawnClass = (UClass*)PawnBlueprint.Object->GeneratedClass;
	}
	// Set the pawn
	DefaultPawnClass = MyPawnClass;
	PlayerControllerClass = ASpookyPlayerController::StaticClass();
}

void ASpookyGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

AEventManager* ASpookyGameMode::InitializeEventManager()
{
	AEventManager* InstantiatedManager = GetWorld()->SpawnActor<AEventManager>();

	return InstantiatedManager;
}

AEventManager* ASpookyGameMode::GetEventManager()
{
	if (!Manager)
	{
		Manager = InitializeEventManager();
	}

	return Manager;
}

void ASpookyGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Manager)
	{
		Manager->EventTick(DeltaSeconds);
	}

	GEngine->AddOnScreenDebugMessage(1001, 5, FColor::Red, TEXT("AEventSystemGameMode ticking"));
}