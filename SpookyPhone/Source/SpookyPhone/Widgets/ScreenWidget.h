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
	void Init();

	// select the next app in the widget
	UFUNCTION()
	void HoverNextApp(ENavigationDirection Direction);
	void HoverApp(int32 RowNumber = 0, int32 AppNumber = 0);

	UFUNCTION()
	void Select();
	void Unselect();

	void AddWidgetToRow(UUIWidget* Widget, int32 Row = -1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Position)
	int32 NumRows;
	
private:
	TArray<TArray<UUIWidget*>> UIElements;

	int32 SelectedRow;
	int32 SelectedUIElement;
};