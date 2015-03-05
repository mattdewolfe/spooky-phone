// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "SpookyPhoneAppWidget.h"
#include "SpookyPhoneWidget.generated.h"

UENUM()
enum ENavigationDirection
{
	Up,
	Down,
	Right,
	Left
};

UCLASS()
class SPOOKYPHONE_API USpookyPhoneWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USpookyPhoneWidget(const FObjectInitializer & ObjectInitializer);

	void Construct_Implementation() override;

	// select the next app in the widget
	UFUNCTION()
	void SelectNextApp(ENavigationDirection Direction);

	UFUNCTION()
	void Select();
	
private:
	TArray<USpookyPhoneAppWidget*> Apps;

	int32 SelectedApp;

	int32 NumRows;
	int32 NumColumns;
};