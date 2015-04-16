// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HideableActor.generated.h"

UCLASS()
class SPOOKYPHONE_API AHideableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHideableActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SetVisibility(bool _isVisible);

	// The group this objects belongs to. The visibility of all objects in the same group are toggled together. 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Visibility)
	uint8 visibilityGroup;

private:
	bool isVisible;	
};
