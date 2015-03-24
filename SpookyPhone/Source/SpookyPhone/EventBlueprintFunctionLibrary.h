// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
};
