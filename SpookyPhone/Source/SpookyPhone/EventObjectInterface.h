// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EventObjectInterface.generated.h"

class AEventManager;
class UEventBlueprintFunctionLibrary;

UENUM()
enum class EEventState : uint8
{
	STARTED,
	PAUSED,
	ENDED
};

/** Class needed to support InterfaceCast(Object) */
UINTERFACE(MinimalAPI)
class UEventObjectInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()	
};

class IEventObjectInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	virtual void Init();

	virtual void Start(bool shouldStartAlone);

	UFUNCTION(BlueprintImplementableEvent, Category = Event)
	void EventUpdate();

	virtual bool TogglePause(bool shouldTogglePauseAlone);

	virtual void End(bool shouldEndAlone);

	FORCEINLINE void SetManager(AEventManager *EventManager) { Manager = EventManager; }

	FORCEINLINE void SetEventState(EEventState state) { EventState = state; }

	FORCEINLINE EEventState GetEventState() { return EventState; }

	FORCEINLINE void SetEventFlag(int32 flag) { EventFlag = flag; }

	FORCEINLINE void SetStartEventFlag(int32 flag) { StartEventFlag = flag; }

	FORCEINLINE void SetPauseEventFlag(int32 flag) { PauseEventFlag = flag; }

	FORCEINLINE void SetEndEventFlag(int32 flag) { EndEventFlag = flag; }

	FORCEINLINE int32 GetEventFlag() { return EventFlag; }

	FORCEINLINE int32 GetStartEventFlag() { return StartEventFlag; }

	FORCEINLINE int32 GetPauseEventFlag() { return PauseEventFlag; }

	FORCEINLINE int32 GetEndEventFlag() { return EndEventFlag; }

private:
	/*
	* Base class should have a way of exposing the variables within blueprint for editing
	* Do this by marking the variables with property modifier
	*/
	int32 EventFlag;

	int32 StartEventFlag;

	int32 PauseEventFlag;

	int32 EndEventFlag;

protected:
	AEventManager* Manager;

	UFunction* EventUpdateFunction;

	EEventState EventState;
};