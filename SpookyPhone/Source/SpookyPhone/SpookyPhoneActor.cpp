// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SpookyPhoneActor.h"

ASpookyPhoneActor::ASpookyPhoneActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Create the phone's static mesh
	m_phoneMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Nexus4"));

	// Load material and static mesh of the	Nexus4
	ConstructorHelpers::FObjectFinder<UStaticMesh> phoneMesh(TEXT("StaticMesh'/Game/Meshes/Nexus4'"));
	ConstructorHelpers::FObjectFinder<UMaterial> phoneMaterial(TEXT("Material'/Game/Materials/Nexus4_Mat'"));

	// Apply material and static mesh
	m_phoneMaterial = phoneMaterial.Object;
	m_phoneMesh->SetMaterial(0, m_phoneMaterial);

	m_phoneMesh->SetStaticMesh(phoneMesh.Object);

	// Create the screen's static mesh
	m_screenMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Screen"));

	// Load the material and static mesh of the screen
	ConstructorHelpers::FObjectFinder<UStaticMesh> screenMesh(TEXT("StaticMesh'/Game/Shapes/Shape_Cube.Shape_Cube'"));
	ConstructorHelpers::FObjectFinder<UMaterial> screenMaterial(TEXT("Material'/Game/Materials/White_Mat'"));

	// Set the position and scale of the screen
	m_screenMaterial = screenMaterial.Object;
	m_screenMesh->SetMaterial(0, m_screenMaterial);

	m_screenMesh->SetStaticMesh(screenMesh.Object);
	m_screenMesh->SetRelativeScale3D(FVector(0.3f, 0.55f, 0.f));
	m_screenMesh->SetRelativeLocation(FVector(0.f, 0.f, 4.59f));

	m_umgPhoneWidget = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("PhoneWidget"));
	m_umgPhoneWidget->SetRelativeScale3D(FVector(0.3f, 0.3f, 1.f));
	m_umgPhoneWidget->SetRelativeLocation(FVector(-15.f, -26.5f, 4.6f));

	// Scene capture 2d
	m_phoneCamera = ObjectInitializer.CreateDefaultSubobject<UChildActorComponent>(this, TEXT("PhoneCamera"));
	m_phoneCamera->ChildActorClass = APhoneCamera::StaticClass();
	m_phoneCamera->SetRelativeRotation(FRotator(0.f, -90.f, -90.f));

	// Root component of this actor is the phone's static mesh
	RootComponent = m_phoneMesh;
	m_screenMesh->AttachTo(RootComponent);
	m_umgPhoneWidget->AttachTo(RootComponent);
	m_phoneCamera->AttachTo(RootComponent);

	m_numApps = 10;
}

void ASpookyPhoneActor::BeginPlay()
{
	Super::BeginPlay();

	m_umgPhoneWidget->SetComponentTickEnabled(false);
	//m_umgPhoneWidget->Deactivate();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("test, %d"), m_umgPhoneWidget->IsActive()));
	}
}