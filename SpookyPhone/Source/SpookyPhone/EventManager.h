// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EventObjectInterface.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "EventManager.generated.h"

/**
* EventManager contains event objects and manages and processes events sequentially
* EventManager inherits from Actor and can be spwned in levels like any other Actor-like objects
*
*/
UCLASS(BlueprintType, Blueprintable, config = Engine)
class SPOOKYPHONE_API AEventManager : public AActor
{
	GENERATED_BODY()

public:
	AEventManager(const FObjectInitializer& ObjectInitializer);

	virtual void PostLoad() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	void Init();

	void RegisterEventObject(IEventObjectInterface* EventObject);

	void AddToUpdateList(IEventObjectInterface* EventObject);

	void RemoveFromUpdateList(IEventObjectInterface* EventObject);

	virtual void EventTick(float DeltaSeconds);

protected:
	TArray<IEventObjectInterface*> EventContainer;

	TArray<IEventObjectInterface*> UpdateList;

	TArray<IEventObjectInterface*> PauseList;
};
