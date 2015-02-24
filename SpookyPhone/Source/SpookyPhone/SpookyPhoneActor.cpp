// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SpookyPhoneActor.h"

ASpookyPhoneActor::ASpookyPhoneActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Create the phone's static mesh
	PhoneMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Nexus4"));

	// Load material and static mesh of the	Nexus4
	ConstructorHelpers::FObjectFinder<UStaticMesh> phoneMesh(TEXT("StaticMesh'/Game/Meshes/Nexus4'"));
	ConstructorHelpers::FObjectFinder<UMaterial> phoneMaterial(TEXT("Material'/Game/Materials/Nexus4_Mat'"));

	// Apply material and static mesh
	PhoneMaterial = phoneMaterial.Object;
	PhoneMesh->SetMaterial(0, PhoneMaterial);

	PhoneMesh->SetStaticMesh(phoneMesh.Object);

	// Create the screen's static mesh
	ScreenMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Screen"));

	// Load the material and static mesh of the screen
	ConstructorHelpers::FObjectFinder<UStaticMesh> screenMesh(TEXT("StaticMesh'/Game/Meshes/Shape_Cube.Shape_Cube'"));
	ConstructorHelpers::FObjectFinder<UMaterial> screenMaterial(TEXT("Material'/Game/Materials/White_Mat'"));

	// Set the position and scale of the screen
	ScreenMaterial = screenMaterial.Object;
	ScreenMesh->SetMaterial(0, ScreenMaterial);

	ScreenMesh->SetStaticMesh(screenMesh.Object);
	ScreenMesh->SetRelativeScale3D(FVector(0.15f, 0.28f, 0.f));
	ScreenMesh->SetRelativeLocation(FVector(0.f, 0.f, 4.59f));

	// Create the widget component
	UMGPhoneWidget = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("PhoneWidget"));
	UMGPhoneWidget->SetRelativeScale3D(FVector(0.3f, 0.3f, 1.f));
	UMGPhoneWidget->SetRelativeLocation(FVector(-15.f, -26.5f, 4.6f));
	UMGPhoneWidget->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));

	// Root component of this actor is the phone's static mesh
	RootComponent = PhoneMesh;
	ScreenMesh->AttachTo(RootComponent);
	UMGPhoneWidget->AttachTo(RootComponent);

	bIsHidden = true;
}

void ASpookyPhoneActor::BeginPlay()
{
	Super::BeginPlay();

	// get a reference to the world
	UWorld* world = GetWorld();

	if (world)
	{
		// spawn the phone near the pawn
		Camera = GetWorld()->SpawnActor<APhoneCamera>(APhoneCamera::StaticClass(), FVector(0.f, 0.f, 0.f), FRotator(0.f, -90.f, -90.f));
		Camera->AttachRootComponentToActor(this, NAME_None, EAttachLocation::KeepRelativeOffset);
	}

	UMGPhoneWidget->Activate();
}

void ASpookyPhoneActor::TogglePhone()
{
	SetActorTickEnabled(bIsHidden);
	SetActorHiddenInGame(bIsHidden);
	bIsHidden = !bIsHidden;
}

void ASpookyPhoneActor::TogglePhoneUI()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("test, %d"), UMGPhoneWidget->IsActive()));
	}

	if (UMGPhoneWidget->IsActive())
	{
		UMGPhoneWidget->Deactivate();
		UMGPhoneWidget->SetHiddenInGame(true);
		UMGPhoneWidget->SetComponentTickEnabled(false);
		UMGPhoneWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UMGPhoneWidget->Activate();
		UMGPhoneWidget->SetHiddenInGame(false);
		UMGPhoneWidget->SetComponentTickEnabled(true);
		UMGPhoneWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}