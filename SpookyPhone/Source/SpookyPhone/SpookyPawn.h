// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "SpookyPhoneActor.h"

#include "SpookyPawn.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API ASpookyPawn : public APawn
{
	GENERATED_BODY()

public:
	ASpookyPawn(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Collision)
	UCapsuleComponent* ColliderComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Movement)
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Phone)
	UClass* PhoneClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Phone)
	ASpookyPhoneActor* Phone;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual void BeginPlay() override;

	void OnEPressed();
	void OnDPressed();
	void OnForward(float value);
};