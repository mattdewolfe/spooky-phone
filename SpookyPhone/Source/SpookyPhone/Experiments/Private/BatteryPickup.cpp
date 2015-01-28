// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeVariant.h"
#include "BatteryPickup.h"

ABatteryPickup::ABatteryPickup(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	PowerLevel = 100.0f;
}

void ABatteryPickup::OnPickedUp_Implementation() 
{
	// Call parent function
	Super::OnPickedUp_Implementation();
	
	// Destroy the battery
	Destroy();
}


