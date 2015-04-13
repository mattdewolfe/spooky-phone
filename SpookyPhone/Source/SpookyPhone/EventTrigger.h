// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EventBlueprintFunctionLibrary.h"
#include "Engine.h"
#include "Engine/TriggerBox.h"
#include "EventTrigger.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API AEventTrigger : public ATriggerBox, public IEventObjectInterface
{
	GENERATED_BODY()

#if WITH_EDITOR
		// Begin AActor interface.
		virtual void EditorApplyScale(const FVector& DeltaScale, const FVector* PivotLocation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;
	// End AActor interface.
#endif

public:
	AEventTrigger(const FObjectInitializer& ObjectInitializer);

	virtual void PreInitializeComponents() override;

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void Start(bool shouldStartAlone) override;

	virtual bool TogglePause(bool shouldTogglePauseAlone) override;

	virtual void End(bool shouldEndAlone) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Event)
	int32 eventFlag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Event)
	int32 startEventFlag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Event)
	int32 pauseEventFlag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Event)
	int32 endEventFlag;
};
