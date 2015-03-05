// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "UIWidget.h"
#include "ScreenWidget.generated.h"

UENUM()
enum ENavigationDirection
{
	Up,
	Down,
	Right,
	Left
};

UCLASS()
class SPOOKYPHONE_API UScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UScreenWidget(const FObjectInitializer & ObjectInitializer);

	void Construct_Implementation() override;

	// select the next app in the widget
	UFUNCTION()
	void SelectNextApp(ENavigationDirection Direction);

	UFUNCTION()
	void Select();
	
private:
	TArray<UUIWidget*> UIElements;

	int32 SelectedUIElement;

	int32 NumRows;
	int32 NumColumns;
};