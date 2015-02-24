// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SPPawn.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API ASPPawn : public ACharacter
{

	GENERATED_BODY()
	ASPPawn(const FObjectInitializer& _ObjectInitializer);

private:
	// Stores value from each axis 
	float leftWheelMotion;
	float rightWheelMotion;
	// Use to determine how much of a difference in axis value we will ignore
	float wheelMotionPrecision;

public:
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UMovementComponent* MovementComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Physics)
	UCapsuleComponent* ColliderComponent;

	virtual void SetupPlayerInputComponent(UInputComponent * _InputComponent) override;
	virtual void Tick(float _DeltaTime);

	// Get rotation function override for implementation of seperating
	// VR look rotation from the pawn rotation
	virtual FRotator GetViewRotation() const override;

	void CalculateAndApplyMovement();
	void LeftWheelMoved(float _value);
	void RightWheelMoved(float _value);
	void MoveForward(float _value);
	void Turn(float _value);

};