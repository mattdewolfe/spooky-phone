// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "EventBlueprintFunctionLibrary.h"

UEventBlueprintFunctionLibrary::UEventBlueprintFunctionLibrary(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void UEventBlueprintFunctionLibrary::StartEvent(const TScriptInterface<IEventObjectInterface> &target)
{
#if WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(1112, 5, FColor::Cyan, TEXT("UEventBlueprintFunctionLibrary Event Started"));
#endif

	target->Start(false);
}

void UEventBlueprintFunctionLibrary::EventTogglePause(const TScriptInterface<IEventObjectInterface> &target)
{
#if WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(1112, 5, FColor::Cyan, TEXT("UEventBlueprintFunctionLibrary Event Paused"));
#endif

	target->TogglePause(false);
}

void UEventBlueprintFunctionLibrary::EndEvent(const TScriptInterface<IEventObjectInterface> &target)
{
#if WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(1112, 5, FColor::Cyan, TEXT("UEventBlueprintFunctionLibrary Event Ended"));
#endif

	target->End(false);
}