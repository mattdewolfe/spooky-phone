// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "EventManager.generated.h"

class IEventObjectInterface;
class UEventBlueprintFunctionLibrary;

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

	void StartEvent(IEventObjectInterface* EventObject);

	void EventTogglePause(IEventObjectInterface* EventObject);

	void EndEvent(IEventObjectInterface* EventObject);

	void RegisterEventObject(IEventObjectInterface* EventObject);

	FORCEINLINE void AddToUpdateList(IEventObjectInterface* EventObject);

	FORCEINLINE void RemoveFromUpdateList(IEventObjectInterface* EventObject);

	FORCEINLINE void RemoveAllFromUpdateList(int32 key);

	virtual void EventTick(float DeltaSeconds);

protected:
	TArray<IEventObjectInterface*> EventContainer;

	TArray<IEventObjectInterface*> UpdateList;

	TArray<IEventObjectInterface*> PauseList;

	TMultiMap<int32, IEventObjectInterface*> EventMap;

	TMultiMap<int32, IEventObjectInterface*> UpdateMap;
};
