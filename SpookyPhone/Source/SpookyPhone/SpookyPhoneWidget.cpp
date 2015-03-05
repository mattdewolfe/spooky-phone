// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SpookyPhoneWidget.h"
#include "SpookyPhoneAppWidget.h"

USpookyPhoneWidget::USpookyPhoneWidget(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	SelectedApp = 0;
	NumRows = 5;
	NumColumns = 3;
}

void USpookyPhoneWidget::Construct_Implementation()
{
	Super::Construct_Implementation();

	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);

	for (UWidget* Widget : Widgets)
	{
		USpookyPhoneAppWidget* App = Cast<USpookyPhoneAppWidget>(Widget);
		if (App)
		{
			Apps.Add(App);
		}
	}

	Apps[SelectedApp]->Select();
}

void USpookyPhoneWidget::SelectNextApp(ENavigationDirection Direction)
{
	if (Apps.Num() == 0)
		return;

	Apps[SelectedApp]->Unselect();

	switch (Direction)
	{
	case Up:
		SelectedApp -= NumColumns;
		if (SelectedApp < 0)
		{
			SelectedApp += Apps.Num();
		}
		break;
	case Down:
		SelectedApp += NumColumns;
		if (SelectedApp >= Apps.Num())
		{
			SelectedApp -= Apps.Num();
		}
		break;
		break;
	case Right:
		SelectedApp++;
		if (SelectedApp >= Apps.Num())
		{
			SelectedApp = 0;
		}
		break;
	case Left:
		SelectedApp--;
		if (SelectedApp < 0)
		{
			SelectedApp = Apps.Num() - 1;
		}
		break;
	}

	Apps[SelectedApp]->Select();
}

void USpookyPhoneWidget::Select()
{
	Apps[SelectedApp]->OnAppClicked();
}