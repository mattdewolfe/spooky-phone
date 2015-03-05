// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "EventManager.h"

AEventManager::AEventManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AEventManager::PostLoad()
{
	Super::PostLoad();

}

void AEventManager::OnConstruction(const FTransform& Transform)
{

}

void AEventManager::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	EventContainer.Empty();
}

void AEventManager::BeginPlay()
{
	Super::BeginPlay();

	//EventContainer[0]->Start();

	//for (auto Itr(EventContainer.CreateIterator()); Itr; Itr++)
	//{
	//	(*Itr)->Start();
	//}
}

void AEventManager::Init()
{
	int i = 0;
}

void AEventManager::EventTick(float DeltaSeconds)
{
	GEngine->AddOnScreenDebugMessage(1002, 5, FColor::Cyan, TEXT("AEventManager ticking"));

	for (auto Itr(UpdateList.CreateIterator()); Itr; Itr++)
	{
		(*Itr)->EventUpdate();
	}
}

void AEventManager::RegisterEventObject(IEventObjectInterface* EventObject)
{
	//Append this event object to the event container if it doesn't already exist in the container
	EventContainer.AddUnique(EventObject);
	EventObject->SetManager(this);
}

void AEventManager::AddToUpdateList(IEventObjectInterface* EventObject)
{
	//Append this event object to the update list if it doesn't already exist in the container
	UpdateList.AddUnique(EventObject);
}

void AEventManager::RemoveFromUpdateList(IEventObjectInterface* EventObject)
{
	UpdateList.Remove(EventObject);
}