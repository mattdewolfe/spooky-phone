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

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Physics)
	UCapsuleComponent* ColliderComponent;

	// Get rotation function override for implementation of seperating
	// VR look rotation from the pawn rotation
	virtual FRotator GetViewRotation() const override;

	void CalculateAndApplyMovement();
	void LeftWheelMoved(float _value);
	void RightWheelMoved(float _value);
	void MoveForward(float _value);
	void Turn(float _value);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Phone)
	UClass* PhoneClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Phone)
	ASpookyPhoneActor* Phone;
	
//	void TogglePhone();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent * _InputComponent) override;
	virtual void Tick(float _DeltaTime);

private:
	// Stores value from each axis 
	float leftWheelMotion;
	float rightWheelMotion;
	// Use to determine how much of a difference in axis value we will ignore
	float wheelMotionPrecision;
};