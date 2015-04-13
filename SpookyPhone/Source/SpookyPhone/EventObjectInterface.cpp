// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "EventBlueprintFunctionLibrary.h"
#include "EventObjectInterface.h"

UEventObjectInterface::UEventObjectInterface(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void IEventObjectInterface::Init()
{

}

void IEventObjectInterface::Start(bool shouldStartAlone)
{
	UEventBlueprintFunctionLibrary::StartEventObject(this, shouldStartAlone);
}

bool IEventObjectInterface::TogglePause(bool shouldTogglePauseAlone)
{
	return UEventBlueprintFunctionLibrary::EventObjectTogglePause(this, shouldTogglePauseAlone);
}

void IEventObjectInterface::End(bool shouldEndAlone)
{
	UEventBlueprintFunctionLibrary::EndEventObject(this, shouldEndAlone);
}