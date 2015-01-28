// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyPickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class CODEVARIANT_API ABatteryPickup : public AMyPickup
{
	GENERATED_UCLASS_BODY()
public:
	// Stores the amount of power this battery will give to the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Power)
	float PowerLevel;
	
	// Override pickup function to define effect of battery pickup
	// We must use implementation because this is a blueprint native event
	void OnPickedUp_Implementation();
};
