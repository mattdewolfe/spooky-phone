// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "SpookyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API ASpookyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void UpdateRotation(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	FRotator GetViewRotation() const;

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void SetViewRotation(const FRotator& NewRotation);

	virtual void SetControlRotation(const FRotator& NewRotation) override;

	UPROPERTY(BlueprintReadWrite, Category = "Cell Bars")
	bool isInService;

protected:

	/**
	*  View & Movement direction are now separate.
	*  The controller rotation will determine which direction we will move.
	*  ViewRotation represents where we are looking.
	*/
	UPROPERTY()
	FRotator ViewRotation;

};

