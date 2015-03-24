// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "ScreenWidget.h"
#include "UIWidget.h"

UScreenWidget::UScreenWidget(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	SelectedRow = 0;
	SelectedUIElement = 0;

	//for (int i = 0; i < NumRows; i++)
		//UIElements.Add(TArray<UUIWidget*>());
}

void UScreenWidget::Init()
{
	for (int i = 0; i < NumRows; i++)
		UIElements.Add(TArray<UUIWidget*>());
}

void UScreenWidget::Construct_Implementation()
{
	Super::Construct_Implementation();

	//UIElements.Empty();

	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);

	for (UWidget* Widget : Widgets)
	{
		UUIWidget* App = Cast<UUIWidget>(Widget);
		if (App)
		{
			UIElements[App->RowNumber].Add(App);
		}
	}

	UIElements[SelectedRow][SelectedUIElement]->Select();
}

void UScreenWidget::HoverNextApp(ENavigationDirection Direction)
{
	if (UIElements.Num() == 0)
		return;

	UIElements[SelectedRow][SelectedUIElement]->Unselect();

	switch (Direction)
	{
	case Up:
		SelectedRow--;
		if (SelectedRow < 0)
		{
			SelectedRow = NumRows - 1;
		}
		if (SelectedUIElement >= UIElements[SelectedRow].Num())
			SelectedUIElement = UIElements[SelectedRow].Num() - 1;
		break;
	case Down:
		SelectedRow++;
		if (SelectedRow >= NumRows)
		{
			SelectedRow = 0;
		}
		if (SelectedUIElement >= UIElements[SelectedRow].Num())
			SelectedUIElement = UIElements[SelectedRow].Num() - 1;
		break;
	case Right:
		SelectedUIElement++;
		if (SelectedUIElement >= UIElements[SelectedRow].Num())
		{
			SelectedUIElement = 0;
		}
		break;
	case Left:
		SelectedUIElement--;
		if (SelectedUIElement < 0)
		{
			SelectedUIElement = UIElements[SelectedRow].Num() - 1;
		}
		break;
	}

	UIElements[SelectedRow][SelectedUIElement]->Select();
}

void UScreenWidget::HoverApp(int32 RowNumber /*= 0*/, int32 AppNumber /*= 0*/)
{
	UIElements[SelectedRow][SelectedUIElement]->Unselect();
	
	SelectedRow = RowNumber;
	SelectedUIElement = AppNumber;

	UIElements[SelectedRow][SelectedUIElement]->Select();
}

void UScreenWidget::Select()
{
	UIElements[SelectedRow][SelectedUIElement]->OnAppClicked();
}

void UScreenWidget::Unselect()
{
	UIElements[SelectedRow][SelectedUIElement]->Unselect();
}

void UScreenWidget::AddWidgetToRow(UUIWidget* Widget, int32 Row /*= -1*/)
{
	if (Row < 0 || Row >= NumRows)
	{
		UIElements.Add(TArray<UUIWidget*>());
		Row = NumRows;
		NumRows++;
	}

	UIElements[Row].Add(Widget);
}