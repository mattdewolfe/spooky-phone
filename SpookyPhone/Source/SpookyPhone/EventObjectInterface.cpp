// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
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

}

bool IEventObjectInterface::TogglePause(bool shouldTogglePauseAlone)
{
	return EventState == EEventState::PAUSED;
}

void IEventObjectInterface::End(bool shouldEndAlone)
{

}