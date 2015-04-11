// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SPInGameClock.h"


// Sets default values
ASPInGameClock::ASPInGameClock(const FObjectInitializer& _init) :
timeToPlay(300)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Asset, Reference Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	baseMesh = StaticMeshOb.Object;

	//Create
	minutesSM = _init.CreateDefaultSubobject < UStaticMeshComponent >(this, TEXT("ClockMinuteMesh"));
	semicolonSM = _init.CreateDefaultSubobject < UStaticMeshComponent >(this, TEXT("ClockSemiColonMesh"));
	powerOf10SecondsSM = _init.CreateDefaultSubobject < UStaticMeshComponent >(this, TEXT("ClockPower10Mesh"));
	secondsSM = _init.CreateDefaultSubobject < UStaticMeshComponent >(this, TEXT("ClockSecondMesh"));

	//Set Mesh
	minutesSM->SetStaticMesh(baseMesh);
	semicolonSM->SetStaticMesh(baseMesh);
	powerOf10SecondsSM->SetStaticMesh(baseMesh);
	secondsSM->SetStaticMesh(baseMesh);

	minutesSM->SetWorldScale3D(FVector(0.45, 0.2, 0.2));

	//Deferred Attachment (Ty Nick W.! Actual attach gets done after blueprint stuff)
	RootComponent = minutesSM;
	semicolonSM->AttachParent = minutesSM;
	powerOf10SecondsSM->AttachParent = minutesSM;
	secondsSM->AttachParent = minutesSM;

	timeRemaining = timeToPlay;
}

// Called when the game starts or when spawned
void ASPInGameClock::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASPInGameClock::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	timeRemaining -= DeltaTime;
}

void ASPInGameClock::UpdateClock()
{
	if (timeRemaining > 0)
	{
		uint32 temp = timeRemaining;
		SetMinutes(temp / 60);
		temp %= 60;
		SetPower10Seconds(temp/10);
		SetSeconds(temp % 10);
	}
}

void ASPInGameClock::SetSeconds(uint32 _val)
{
	if (currentSecondTime != _val)
	{
		currentSecondTime = _val;
		UMaterialInterface* tempMat = Cast<UMaterialInterface>(clockFrames[currentSecondTime]);
		secondsSM->SetMaterial(0, tempMat);
	}
}

void ASPInGameClock::SetMinutes(uint32 _val)
{
	if (currentMinuteTime != _val)
	{
		currentMinuteTime = _val;
		UMaterialInterface* tempMat = Cast<UMaterialInterface>(clockFrames[currentMinuteTime]);
		secondsSM->SetMaterial(0, tempMat);
	}
}

void ASPInGameClock::SetPower10Seconds(uint32 _val)
{
	if (currentPower10SecondTime != _val)
	{
		currentPower10SecondTime = _val;
		UMaterialInterface* tempMat = Cast<UMaterialInterface>(clockFrames[currentPower10SecondTime]);
		secondsSM->SetMaterial(0, tempMat);
	}
}
