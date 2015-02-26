// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EventManager.h"
#include "SpookyGameMode.h"
#include "Engine.h"
#include "EventObjectInterface.h"
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

	UFUNCTION(BlueprintCallable, Category = Event)
	virtual void Start() override;

	virtual void EventUpdate() override;

	UFUNCTION(BlueprintCallable, Category = Event)
	virtual void End() override;
};
