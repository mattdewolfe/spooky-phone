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
	//32-bits so maximum bit index in uint64 integer would be 31 (32 - 1)
	uint64 flag = 1;
	flag <<= 31;

	//Tell Manager to pause other flagged events same as PauseEventFlag
	int32 tempBitMask = 1;

	while (tempBitMask <= flag)
	{
		//Adds all possible keys to EventMap
		EventMap.Add(flag);
		UpdateMap.Add(flag);

		if (tempBitMask == flag)
		{
			break;
		}

		tempBitMask <<= 1;
	}
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
}

void AEventManager::EventTick(float DeltaSeconds)
{
#if WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(1002, 5, FColor::Cyan, TEXT("AEventManager ticking"));
#endif

	//for (auto Itr(UpdateList.CreateIterator()); Itr; Itr++)
	//{
	//	auto t = Cast<UObject>(*Itr);
	//	(*Itr)->Execute_EventUpdate(t);
	//}

	for (auto Itr(UpdateMap.CreateIterator()); Itr; ++Itr)
	{
		IEventObjectInterface* eventObject = Itr.Value();

		auto t = Cast<UObject>(eventObject);

		if (eventObject && t && eventObject->GetEventState() != EEventState::PAUSED)
		{
			eventObject->Execute_EventUpdate(t);
		}
	}
}

void AEventManager::StartEvent(IEventObjectInterface* EventObject)
{
	AddToUpdateList(EventObject);

	int32 StartEventFlag = EventObject->GetStartEventFlag();

	if (StartEventFlag > 0)
	{
		//Tell Manager to start other flagged events same as StartEventFlag
		int32 tempBitMask = 1;

		while (tempBitMask <= StartEventFlag)
		{
			//If bit flag at specific location is on
			if (StartEventFlag & tempBitMask)
			{
#if WITH_EDITOR
				GEngine->AddOnScreenDebugMessage(1111, 5, FColor::White, TEXT("Starting Other Events With Flag"));
#endif
				//Iterates through all values associated with this specific bit flag
				for (auto Itr(EventMap.CreateKeyIterator(StartEventFlag)); Itr; ++Itr)
				{
					IEventObjectInterface* eventObject = Itr.Value();
					if (eventObject)
					{
						eventObject->Start(true);
					}
				}
			}

			if (tempBitMask == StartEventFlag)
			{
				break;
			}

			tempBitMask <<= 1;
		}
	}
}

void AEventManager::EventTogglePause(IEventObjectInterface* EventObject)
{
	int32 PauseEventFlag = EventObject->GetPauseEventFlag();

	if (PauseEventFlag > 0)
	{
		//Tell Manager to pause other flagged events same as PauseEventFlag
		int32 tempBitMask = 1;

		while (tempBitMask <= PauseEventFlag)
		{
			//If bit flag at specific location is on
			if (PauseEventFlag & tempBitMask)
			{
#if WITH_EDITOR
				GEngine->AddOnScreenDebugMessage(1111, 5, FColor::White, TEXT("Pausing Other Events With Flag"));
#endif
				//Iterates through all values associated with this specific bit flag
				for (auto Itr(EventMap.CreateKeyIterator(PauseEventFlag)); Itr; ++Itr)
				{
					Itr.Value()->TogglePause(true);
				}
			}

			if (tempBitMask == PauseEventFlag)
			{
				break;
			}

			tempBitMask <<= 1;
		}
	}
}

void AEventManager::EndEvent(IEventObjectInterface* EventObject)
{
	RemoveFromUpdateList(EventObject);

	int32 EndEventFlag = EventObject->GetEndEventFlag();

	if (EndEventFlag > 0)
	{
		//Tell Manager to end other flagged events same as EndEventFlag
		int32 tempBitMask = 1;

		while (tempBitMask <= EndEventFlag)
		{
			//If bit flag at specific location is on
			if (EndEventFlag & tempBitMask)
			{
#if WITH_EDITOR
				GEngine->AddOnScreenDebugMessage(1111, 5, FColor::White, TEXT("Ending Other Events With Flag"));
#endif
				//Iterates through all values associated with this specific bit flag
				for (auto Itr(EventMap.CreateKeyIterator(EndEventFlag)); Itr; ++Itr)
				{
					IEventObjectInterface* eventObject = Itr.Value();

					if (eventObject)
					{
						eventObject->End(true);
					}
				}
			}

			if (tempBitMask == EndEventFlag)
			{
				break;
			}

			tempBitMask <<= 1;
		}

		RemoveAllFromUpdateList(EndEventFlag);
	}
}

void AEventManager::RegisterEventObject(IEventObjectInterface* EventObject)
{
	//Append this event object to the event container if it doesn't already exist in the container
	//EventContainer.AddUnique(EventObject);
	EventMap.AddUnique(EventObject->GetEventFlag(), EventObject);
	EventObject->SetManager(this);
}

void AEventManager::AddToUpdateList(IEventObjectInterface* EventObject)
{
	//Append this event object to the update list if it doesn't already exist in the container
	//UpdateList.AddUnique(EventObject);
	UpdateMap.AddUnique(EventObject->GetStartEventFlag(), EventObject);
}

void AEventManager::RemoveFromUpdateList(IEventObjectInterface* EventObject)
{
	//UpdateList.Remove(EventObject);
	UpdateMap.RemoveSingle(EventObject->GetStartEventFlag(), EventObject);
}

void AEventManager::RemoveAllFromUpdateList(int32 key)
{
	UpdateMap.Remove(key);
}