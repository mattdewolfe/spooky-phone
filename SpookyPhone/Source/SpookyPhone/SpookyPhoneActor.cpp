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
	UMGPhoneHomeWidget = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("HomeButtonWidget"));
	//UMGPhoneHomeWidget->SetRelativeScale3D(FVector(0.3f, 0.3f, 1.f));
	//UMGPhoneHomeWidget->SetRelativeLocation(FVector(-15.f, -26.5f, 4.6f));
	//UMGPhoneHomeWidget->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));

	ConstructorHelpers::FObjectFinder<UBlueprint> phoneWidgetBlueprint(TEXT("Blueprint'/Game/Blueprints/BP_Screens.BP_Screens'"));
	if (phoneWidgetBlueprint.Object)
	{
		PhoneWidgetBlueprint = (UClass*)phoneWidgetBlueprint.Object->GeneratedClass;
	}

	// Root component of this actor is the phone's static mesh
	RootComponent = PhoneMesh;
	ScreenMesh->AttachTo(RootComponent);
	UMGPhoneHomeWidget->AttachTo(RootComponent);

	CurrentScreen = EScreens::HOME;
	bIsHidden = false;
}

void ASpookyPhoneActor::BeginPlay()
{
	Super::BeginPlay();

	// get a reference to the world
	UWorld* World = GetWorld();

	if (World)
	{
		// Spawn the camera for the phone
		Camera = World->SpawnActor<APhoneCamera>(APhoneCamera::StaticClass(), GetActorForwardVector() * FVector(0.f, 10.f, 0.f), FRotator(-90.f, 0.f, -90.f));
		Camera->AttachRootComponentToActor(this, NAME_None, EAttachLocation::KeepRelativeOffset);
		Camera->SetActorHiddenInGame(true);

		// Setup the home button
		UMGPhoneHomeWidget->Activate();
		UMGHomeButton = Cast<UUIWidget>(UMGPhoneHomeWidget->GetUserWidgetObject());

		// Spawn all of the screens
		PhoneUI = GetWorld()->SpawnActor<AActor>(PhoneWidgetBlueprint, FVector::ZeroVector, FRotator::ZeroRotator);
		PhoneUI->AttachRootComponentToActor(this, NAME_None, EAttachLocation::KeepRelativeOffset);

		// Load the screens into relative arrays
		TArray<UActorComponent*> Screens = PhoneUI->GetComponents();
		ScreenWidgetComponents.AddZeroed(Screens.Num());
		ScreenWidgets.AddZeroed(Screens.Num());
		for (int32 i = 0; i < Screens.Num(); i++)
		{
			ScreenWidgetComponents[i] = Cast<UWidgetComponent>(Screens[i]);
			ScreenWidgets[i] = Cast<UScreenWidget>(ScreenWidgetComponents[i]->GetUserWidgetObject());

			ScreenWidgets[i]->Init();
			ScreenWidgets[i]->AddWidgetToRow(UMGHomeButton);

			if (i == 0)
			{
				ScreenWidgetComponents[i]->SetRelativeLocation(FVector(0.f, 0.f, 4.61f));
				ScreenWidgetComponents[i]->SetRelativeScale3D(FVector(0.3f, 0.3f, 1.f));
			}
		
			if (i != CurrentScreen)
				ScreenWidgetComponents[i]->SetVisibility(false);
		}
	}

	GoToScreen(CurrentScreen);
	TogglePhone();
}

void ASpookyPhoneActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASpookyPhoneActor::TogglePhone()
{
	SetActorHiddenInGame(!bIsHidden);
	PhoneUI->SetActorHiddenInGame(!bIsHidden);
	bIsHidden = !bIsHidden;
}

void ASpookyPhoneActor::GoToScreen(EScreens Screen)
{
	if (Screen == CurrentScreen)
		return;

	if (CurrentScreen == EScreens::CAMERA)
	{
		Camera->SetActorTickEnabled(false);
		ScreenMesh->SetMaterial(0, ScreenMaterial);
	}
	else if (Screen == EScreens::CAMERA)
	{
		Camera->SetActorTickEnabled(true);
		ScreenMesh->SetMaterial(0, Camera->cameraMaterial);
	}

	ScreenWidgetComponents[CurrentScreen]->SetVisibility(false);
	ScreenWidgets[CurrentScreen]->Unselect();

	CurrentScreen = Screen;
	
	ScreenWidgetComponents[CurrentScreen]->SetVisibility(true);

	ScreenWidgets[CurrentScreen]->HoverApp();
}

void ASpookyPhoneActor::NavigateByDirection(ENavigationDirection Direction)
{
	ScreenWidgets[CurrentScreen]->HoverNextApp(Direction);
}

void ASpookyPhoneActor::Select()
{
	ScreenWidgets[CurrentScreen]->Select();
}