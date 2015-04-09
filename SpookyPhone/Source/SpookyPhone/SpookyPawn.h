// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EventObjectInterface.h"
#include "SpookyGameMode.h"
#include "EventManager.h"
#include "GameFramework/Character.h"
#include "SpookyPhoneActor.h"
#include "SpookyPlayerController.h"
#include "SpookyPawn.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API ASpookyPawn : public ACharacter, public IEventObjectInterface
{
	GENERATED_BODY()

public:
	ASpookyPawn(const FObjectInitializer& ObjectInitializer);

	// Get rotation function override for implementation of seperating
	// VR look rotation from the pawn rotation
	virtual FRotator GetViewRotation() const override;

	void CalculateAndApplyMovement();
	void LeftWheelMoved(float _value);
	void RightWheelMoved(float _value);
	void MoveForward(float _value);
	void Turn(float _value);

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent * _InputComponent) override;
	virtual void Tick(float _DeltaTime);

	virtual void Start(bool shouldStartAlone) override;

	virtual bool TogglePause(bool shouldTogglePauseAlone) override;

	virtual void End(bool shouldEndAlone) override;

public:
//	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Movement)
//	UMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Physics)
	UCapsuleComponent* ColliderComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Phone)
	UClass* PhoneClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Phone)
	ASpookyPhoneActor* Phone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Event)
	int32 eventFlag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Event)
	int32 startEventFlag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Event)
	int32 pauseEventFlag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Event)
	int32 endEventFlag;

private:
	// Instance of custom player controller for accessing properties
	ASpookyPlayerController* playerController;

	void TogglePhone();
	
	void NavigatePhoneUp();
	void NavigatePhoneDown();
	void NavigatePhoneLeft();
	void NavigatePhoneRight();
	void Use();

	bool bUsingPhone;

	// Stores value from each axis 
	float leftWheelMotion;
	float rightWheelMotion;

	// Use to determine how much of a difference in axis value we will ignore
	float wheelMotionPrecision;
};