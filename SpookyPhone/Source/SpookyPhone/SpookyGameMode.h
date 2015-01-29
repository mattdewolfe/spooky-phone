// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	ASpookyGameMode(const FObjectInitializer& ObjectInitializer);
	void StartPlay() override;
	
};
