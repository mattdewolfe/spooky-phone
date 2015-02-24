// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "SpookyPhoneWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API USpookyPhoneWidget : public UUserWidget
{
	GENERATED_BODY()

	// handle keyboard input on the widget
	virtual FEventReply OnKeyDown_Implementation(FGeometry MyGeometry, FKeyboardEvent InKeyboardEvent) override;

	void Construct_Implementation() override;

	void AddButton();
	
private:
	// select the next app in the widget
	UFUNCTION()
	void SelectNextApp();

	UPROPERTY()
	bool bLockControls;

	UPROPERTY(VisibleDefaultsOnly)
	int32 Apps;
};