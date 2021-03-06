// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EventManager.h"
#include "GameFramework/GameMode.h"
#include "SpookyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API ASpookyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASpookyGameMode(const FObjectInitializer& _ObjectInitializer);

	virtual void PreInitializeComponents() override;

	AEventManager* GetEventManager();

	virtual void Tick(float DeltaSeconds) override;

protected:
	//TSubclassOf<AEventManager> Manager;
	AEventManager* Manager;

protected:
	AEventManager* InitializeEventManager();
};
