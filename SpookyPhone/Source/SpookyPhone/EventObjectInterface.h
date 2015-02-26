// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EventObjectInterface.generated.h"

class AEventManager;

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

	virtual void Start();

	virtual void EventUpdate();

	virtual void End();

	void SetManager(AEventManager *EventManager) { Manager = EventManager; }

protected:
	AEventManager* Manager;

	UFunction* EventUpdateFunction;
};