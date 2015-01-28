// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyPickup.generated.h"

/**
 * 
 */
UCLASS()
class CODEVARIANT_API AMyPickup : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	// True when the pickup is able to be grabbed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	bool bIsActive;

	// Simple collision component, used for root component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	USphereComponent* BaseCollisionComponent;

	// Static mesh component to represent the pickup
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	UStaticMeshComponent* PickupMesh;

	// Function to be called when the pickup is collected
	UFUNCTION(BlueprintNativeEvent)
	void OnPickedUp();
	
};
