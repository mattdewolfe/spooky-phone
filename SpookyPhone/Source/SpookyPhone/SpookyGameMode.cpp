// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SpookyGameMode.h"
#include "SpookyPlayerController.h"
#include "SpookyPawn.h"

ASpookyGameMode::ASpookyGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//UClass* MyPawnClass = ASpookyPawn::StaticClass();
	//ConstructorHelpers::FObjectFinder<UBlueprint> PawnBlueprint(TEXT("Blueprint'/Game/Blueprints/BP_SpookyPawn.BP_SpookyPawn'"));
	//if (PawnBlueprint.Object != NULL)
	//{
	//	MyPawnClass = (UClass*)PawnBlueprint.Object->GeneratedClass;
	//}

	DefaultPawnClass = ASpookyPawn::StaticClass();
	PlayerControllerClass = ASpookyPlayerController::StaticClass();
}

void ASpookyGameMode::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		
	}
}