// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpookyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ReceptionBar.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API UReceptionBar : public UUserWidget
{
	GENERATED_BODY()

private: 
	TArray<UImage*> bars;
	ASpookyPlayerController* controller;

	bool lastChange;
public:
	virtual void Construct_Implementation() override;
	
	void ToggleBarsEnabled(bool _new);

	UFUNCTION(BlueprintCallable, Category = "TickOnwards")
	void CheckControllerBool();
	
};