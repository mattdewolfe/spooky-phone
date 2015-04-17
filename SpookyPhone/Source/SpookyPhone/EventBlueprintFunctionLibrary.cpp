// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "EventBlueprintFunctionLibrary.h"

AEventManager* UEventBlueprintFunctionLibrary::EventManagerInst;

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

AEventManager* UEventBlueprintFunctionLibrary::GetEventManagerInst(UWorld* World)
{
	if (!EventManagerInst->IsValidLowLevel())
	{
		EventManagerInst = World->SpawnActor<AEventManager>();
	}

	return EventManagerInst;
}

void UEventBlueprintFunctionLibrary::StartEventObject(IEventObjectInterface* EventObject, bool shouldStartAlone)
{
	if (EventManagerInst)
	{
		shouldStartAlone ? EventManagerInst->AddToUpdateList(EventObject) : EventManagerInst->StartEvent(EventObject);

		EventObject->SetEventState(EEventState::STARTED);
	}
}

void UEventBlueprintFunctionLibrary::EndEventObject(IEventObjectInterface* EventObject, bool shouldEndAlone)
{
	if (EventManagerInst)
	{
		shouldEndAlone ? EventManagerInst->RemoveFromUpdateList(EventObject) : EventManagerInst->EndEvent(EventObject);

		EventObject->SetEventState(EEventState::ENDED);
	}
}

bool UEventBlueprintFunctionLibrary::EventObjectTogglePause(IEventObjectInterface* EventObject, bool shouldTogglePauseAlone)
{
	if (!shouldTogglePauseAlone)
		EventManagerInst->EventTogglePause(EventObject);

	EEventState state;

	switch (EventObject->GetEventState())
	{
	case EEventState::STARTED:
		state = EEventState::PAUSED;
		EventObject->SetEventState(state);
		break;
	case EEventState::PAUSED:
		state = EEventState::STARTED;
		EventObject->SetEventState(state);
		break;
	}

	return state == EEventState::PAUSED;
}

void UEventBlueprintFunctionLibrary::UpdateEventEventObjectMap(TMultiMap<int32, IEventObjectInterface*> &UpdateMap)
{
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

void UEventBlueprintFunctionLibrary::StartOtherEventObjects(AEventManager* EventManager, IEventObjectInterface* EventObject, TMultiMap<int32, IEventObjectInterface*> &EventMap)
{
	EventManager->AddToUpdateList(EventObject);

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

void UEventBlueprintFunctionLibrary::TogglePauseOtherEventObjects(IEventObjectInterface* EventObject, TMultiMap<int32, IEventObjectInterface*> &EventMap)
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

void UEventBlueprintFunctionLibrary::EndOtherEventObjects(AEventManager* EventManager, IEventObjectInterface* EventObject, TMultiMap<int32, IEventObjectInterface*> &EventMap)
{
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

		EventManager->RemoveAllFromUpdateList(EndEventFlag);
	}
}