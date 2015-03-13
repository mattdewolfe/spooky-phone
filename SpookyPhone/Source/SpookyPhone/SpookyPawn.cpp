// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SpookyPawn.h"
#include "SpookyPlayerController.h"

ASpookyPawn::ASpookyPawn(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer)
{
	ColliderComponent = _ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("ColliderComponent"));
	ColliderComponent->SetCapsuleSize(7.0f, 7.0f);
	RootComponent = ColliderComponent;

	MovementComponent = _ObjectInitializer.CreateDefaultSubobject<UFloatingPawnMovement>(this, TEXT("MovementComponent"));

	PhoneClass = ASpookyPawn::StaticClass();
	ConstructorHelpers::FObjectFinder<UBlueprint> PhoneBlueprint(TEXT("Blueprint'/Game/Blueprints/BP_SpookyPhone.BP_SpookyPhone'"));
	if (PhoneBlueprint.Object != NULL)
	{
		PhoneClass = (UClass*)PhoneBlueprint.Object->GeneratedClass;
	}

	PrimaryActorTick.bCanEverTick = true;
	wheelMotionPrecision = 0.2f;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	bUsingPhone = false;
}

void ASpookyPawn::BeginPlay()
{
	Super::BeginPlay();

	// get a reference to the world
	UWorld* World = GetWorld();

	if (World)
	{
		// spawn the phone near the pawn
		Phone = GetWorld()->SpawnActor<ASpookyPhoneActor>(PhoneClass, FVector(90.f, 0.f, 50.f), FRotator(0.f, 90.f, 90.f));
		Phone->AttachRootComponentToActor(this, NAME_None, EAttachLocation::KeepRelativeOffset);
	}
}

void ASpookyPawn::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (!bUsingPhone)
		CalculateAndApplyMovement();
}

// First attempt at tank controls for wheelchair.
// This is garbage at the moment, and does not factor in new
// Rift view rotation code
void ASpookyPawn::CalculateAndApplyMovement()
{
	// For the time being, we are multiplaying input values by magical floats in 
	// order to slow down the speed of rotation and movement

	// If left wheel is not moving, and right is
	if (abs(leftWheelMotion) <= 0.1f && rightWheelMotion != 0.0f)
	{
		// Add rights negative yaw motion
		AddControllerYawInput(rightWheelMotion*0.25);
	}
	// If left wheel is moving and right is not
	else if (leftWheelMotion != 0.0f && abs(rightWheelMotion) <= 0.1f)
	{
		// Add lefts yaw motion
		AddControllerYawInput(leftWheelMotion*0.25);
	}
	// If both are non zero, combine for yaw and movement
	else if (abs(rightWheelMotion) >= 0.1f && abs(leftWheelMotion) >= 0.1f)
	{
		AddControllerYawInput((leftWheelMotion + rightWheelMotion)*0.2);
		AddMovementInput(GetControlRotation().Vector(), (leftWheelMotion - rightWheelMotion)*0.5);
	}
}

void ASpookyPawn::SetupPlayerInputComponent(UInputComponent * _InputComponent)
{
	// Normal fps setup
	//	_InputComponent->BindAxis("MoveForward", this, &ASpookyPawn::MoveForward);
	//	_InputComponent->BindAxis("Turn", this, &ASpookyPawn::Turn);
	_InputComponent->BindAxis("LeftWheel", this, &ASpookyPawn::LeftWheelMoved);
	_InputComponent->BindAxis("RightWheel", this, &ASpookyPawn::RightWheelMoved);
	_InputComponent->BindAction("TogglePhone", IE_Pressed, this, &ASpookyPawn::TogglePhone);

	_InputComponent->BindAction("NavigationUp", IE_Pressed, this, &ASpookyPawn::NavigatePhoneUp);
	_InputComponent->BindAction("NavigationDown", IE_Pressed, this, &ASpookyPawn::NavigatePhoneDown);
	_InputComponent->BindAction("NavigationLeft", IE_Pressed, this, &ASpookyPawn::NavigatePhoneLeft);
	_InputComponent->BindAction("NavigationRight", IE_Pressed, this, &ASpookyPawn::NavigatePhoneRight);

	_InputComponent->BindAction("Use", IE_Pressed, this, &ASpookyPawn::Use);
}

void ASpookyPawn::LeftWheelMoved(float _value)
{
	leftWheelMotion = _value;
}

void ASpookyPawn::RightWheelMoved(float _value)
{
	rightWheelMotion = _value;
}

void ASpookyPawn::MoveForward(float _value)
{
	AddMovementInput(GetControlRotation().Vector(), _value);
}

void ASpookyPawn::Turn(float _value)
{
	AddControllerYawInput(_value);
}

// Get our view rotation (from controller)
FRotator ASpookyPawn::GetViewRotation() const
{
	if (ASpookyPlayerController* MYPC = Cast<ASpookyPlayerController>(Controller))
	{
		return MYPC->GetViewRotation();
	}
	return GetActorRotation();
}

void ASpookyPawn::TogglePhone()
{
	bUsingPhone = !bUsingPhone;
	Phone->TogglePhone();
}

void ASpookyPawn::NavigatePhoneUp()
{
	if (bUsingPhone)
		Phone->NavigateByDirection(ENavigationDirection::Up);
}

void ASpookyPawn::NavigatePhoneDown()
{
	if (bUsingPhone)
		Phone->NavigateByDirection(ENavigationDirection::Down);
}

void ASpookyPawn::NavigatePhoneLeft()
{
	if (bUsingPhone)
		Phone->NavigateByDirection(ENavigationDirection::Left);
}

void ASpookyPawn::NavigatePhoneRight()
{
	if (bUsingPhone)
		Phone->NavigateByDirection(ENavigationDirection::Right);
}

void ASpookyPawn::Use()
{
	if (bUsingPhone)
		Phone->Select();
}