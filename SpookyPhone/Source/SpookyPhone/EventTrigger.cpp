// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "EventTrigger.h"

AEventTrigger::AEventTrigger(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//AEventManager::RegisterEventObject(this);

	//static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/EventTrigger'"));
	//if (PlayerPawnObject.Object != NULL)
	//{
	//	EventUpdateFunction = ((UClass*)PlayerPawnObject.Object->GeneratedClass)->FindFunctionByName(TEXT("OnEventUpdate"));
	//}
}

void AEventTrigger::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AEventTrigger::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetEventFlag(eventFlag);
	SetStartEventFlag(startEventFlag);
	SetPauseEventFlag(pauseEventFlag);
	SetEndEventFlag(endEventFlag);

	ASpookyGameMode* GameMode = GetWorld()->GetAuthGameMode<ASpookyGameMode>();

	if (GameMode)
	{
		AEventManager* Manager = GameMode->GetEventManager();
		if (Manager)
		{
			Manager->RegisterEventObject(this);
		}
	}
}

void AEventTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void AEventTrigger::EditorApplyScale(const FVector& DeltaScale, const FVector* PivotLocation, bool bAltDown, bool bShiftDown, bool bCtrlDown)
{
	const FVector ModifiedScale = DeltaScale * (AActor::bUsePercentageBasedScaling ? 500.0f : 5.0f);

	UBoxComponent * BoxComponent = Cast<UBoxComponent>(GetRootComponent());
	if (bCtrlDown)
	{
		// CTRL+Scaling modifies trigger collision height.  This is for convenience, so that height
		// can be changed without having to use the non-uniform scaling widget (which is
		// inaccessable with spacebar widget cycling).
		FVector Extent = BoxComponent->GetUnscaledBoxExtent() + FVector(0, 0, ModifiedScale.X);
		Extent.Z = FMath::Max(0.0f, Extent.Z);
		BoxComponent->SetBoxExtent(Extent);
	}
	else
	{
		FVector Extent = BoxComponent->GetUnscaledBoxExtent() + FVector(ModifiedScale.X, ModifiedScale.Y, ModifiedScale.Z);
		Extent.X = FMath::Max(0.0f, Extent.X);
		Extent.Y = FMath::Max(0.0f, Extent.Y);
		Extent.Z = FMath::Max(0.0f, Extent.Z);
		BoxComponent->SetBoxExtent(Extent);
	}
}

void AEventTrigger::Start(bool shouldStartAlone)
{
	// Begin running this event object and register for update until it ends
	// Allow any concurrent event object to keep running but others will be unregistered from EventManager
#if WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(1003, 5, FColor::Blue, FString::Printf(TEXT("AEventTrigger event started")));
#endif

	if (Manager)
	{
		shouldStartAlone ? Manager->AddToUpdateList(this) : Manager->StartEvent(this);

		EventState = EEventState::STARTED;
	}
}

bool AEventTrigger::TogglePause(bool shouldTogglePauseAlone)
{
	if (!shouldTogglePauseAlone)
		Manager->EventTogglePause(this);

	switch (EventState)
	{
	case EEventState::STARTED:
		EventState = EEventState::PAUSED;
		break;
	case EEventState::PAUSED:
		EventState = EEventState::STARTED;
		break;
	}

	return EventState == EEventState::PAUSED;
}

void AEventTrigger::End(bool shouldEndAlone)
{
	if (Manager)
	{
		shouldEndAlone ? Manager->RemoveFromUpdateList(this) : Manager->EndEvent(this);

		SetEventState(EEventState::ENDED);
	}
}