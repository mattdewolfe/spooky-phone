// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SpookyPhoneGameMode.h"
#include "SPPawn.h"
#include "SPPlayerController.h"

ASpookyPhoneGameMode::ASpookyPhoneGameMode(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer)
{
	// Setup a base class
	UClass* MyPawnClass = ASPPawn::StaticClass();

/*	We can use this to spawn our pawn based on a blueprint	
// Find a blueprint we have already defined
	ConstructorHelpers::FObjectFinder<UBlueprint> PawnBlueprint(
	TEXT("Blueprint'/Game/TheChair.TheChair'"));
	// Ensure that the blueprint we want exists, if it does not we use a general pawn
	if (PawnBlueprint.Object != NULL)
	{
		MyPawnClass = (UClass*)PawnBlueprint.Object->GeneratedClass;
	}*/

	// Then set our pawn to class we made
	DefaultPawnClass = MyPawnClass;
	// Setup controller
	PlayerControllerClass = ASPPlayerController::StaticClass();
}