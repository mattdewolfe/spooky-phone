// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EventManager.h"
#include "EventObjectInterface.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EventBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API UEventBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Event)
	static void StartEvent(const TScriptInterface<IEventObjectInterface> &target);

	UFUNCTION(BlueprintCallable, Category = Event)
	static void EventTogglePause(const TScriptInterface<IEventObjectInterface> &target);

	UFUNCTION(BlueprintCallable, Category = Event)
	static void EndEvent(const TScriptInterface<IEventObjectInterface> &target);

	static AEventManager* GetEventManagerInst(UWorld* World);

	static void StartEventObject(IEventObjectInterface* EventObject, bool shouldStartAlone);

	static void EndEventObject(IEventObjectInterface* EventObject, bool shouldEndAlone);

	static bool EventObjectTogglePause(IEventObjectInterface* EventObject, bool shouldTogglePauseAlone);

	static void UpdateEventEventObjectMap(TMultiMap<int32, IEventObjectInterface*> &UpdateMap);

	static void StartOtherEventObjects(AEventManager* EventManager, IEventObjectInterface* EventObject, TMultiMap<int32, IEventObjectInterface*> &EventMap);

	static void TogglePauseOtherEventObjects(IEventObjectInterface* EventObject, TMultiMap<int32, IEventObjectInterface*> &EventMap);

	static void EndOtherEventObjects(AEventManager* EventManager, IEventObjectInterface* EventObject, TMultiMap<int32, IEventObjectInterface*> &EventMap);

private:
	static AEventManager* EventManagerInst;
};
