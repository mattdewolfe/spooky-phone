// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SpookyPlayerController.h"
#include "SpookyPawn.h"
#include "SpookyGameMode.h"

ASpookyGameMode::ASpookyGameMode(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer)
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

void ASpookyGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Manager = UEventBlueprintFunctionLibrary::GetEventManagerInst(GetWorld());
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