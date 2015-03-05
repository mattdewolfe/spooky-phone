// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "ScreenWidget.h"
#include "UIWidget.h"

UScreenWidget::UScreenWidget(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	SelectedUIElement = 0;
	NumRows = 5;
	NumColumns = 3;
}

void UScreenWidget::Construct_Implementation()
{
	Super::Construct_Implementation();

	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);

	for (UWidget* Widget : Widgets)
	{
		UUIWidget* App = Cast<UUIWidget>(Widget);
		if (App)
		{
			UIElements.Add(App);
		}
	}

	UIElements[SelectedUIElement]->Select();
}

void UScreenWidget::SelectNextApp(ENavigationDirection Direction)
{
	if (UIElements.Num() == 0)
		return;

	UIElements[SelectedUIElement]->Unselect();

	switch (Direction)
	{
	case Up:
		SelectedUIElement -= NumColumns;
		if (SelectedUIElement < 0)
		{
			SelectedUIElement += UIElements.Num();
		}
		break;
	case Down:
		SelectedUIElement += NumColumns;
		if (SelectedUIElement >= UIElements.Num())
		{
			SelectedUIElement -= UIElements.Num();
		}
		break;
	case Right:
		SelectedUIElement++;
		if (SelectedUIElement >= UIElements.Num())
		{
			SelectedUIElement = 0;
		}
		break;
	case Left:
		SelectedUIElement--;
		if (SelectedUIElement < 0)
		{
			SelectedUIElement = UIElements.Num() - 1;
		}
		break;
	}

	UIElements[SelectedUIElement]->Select();
}

void UScreenWidget::Select()
{
	UIElements[SelectedUIElement]->OnAppClicked();
}