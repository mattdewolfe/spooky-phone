// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeVariant.h"
#include "MyPickup.h"

AMyPickup::AMyPickup(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	// Make the pickup active upon creation
	bIsActive = true;

	// Create the sphere component for root
	BaseCollisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
	// Assign sphere to root component
	RootComponent = BaseCollisionComponent;

	// Create the static mesh, which will be our visual
	PickupMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh"));

	// Turn on physics for this mesh
	PickupMesh->SetSimulatePhysics(true);

	// Attach this mesh to the root
	PickupMesh->AttachTo(RootComponent);
}

// Default behaviour for pickups
void AMyPickup::OnPickedUp_Implementation()
{

}



