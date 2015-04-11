// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "HideableActor.h"


// Sets default values
AHideableActor::AHideableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHideableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHideableActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AHideableActor::SetVisibility(bool _isVisible)
{
	isVisible = _isVisible;
	SetActorHiddenInGame(isVisible);
}

