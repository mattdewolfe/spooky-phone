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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCapsuleComponent* ColliderComponent;

	virtual void SetupPlayerInputComponent(UInputComponent * _InputComponent) override;
	virtual void Tick(float _DeltaTime);
	virtual FRotator GetViewRotation() const override;

	void CalculateAndApplyMovement();
	void LeftWheelMovement(float _value);
	void RightWheelMovement(float _value);

};