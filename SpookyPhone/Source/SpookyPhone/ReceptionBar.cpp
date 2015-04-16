// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "ReceptionBar.h"

void UReceptionBar::Construct_Implementation()
{
	Super::Construct_Implementation();

	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);

	for (UWidget* Widget : Widgets)
	{
		UImage* App = Cast<UImage>(Widget);

		if (App)
		{
			bars.Add(App);
		}
	}

	controller = Cast<ASpookyPlayerController>(GetWorld()->GetFirstPlayerController());
	lastChange = false;


}

void UReceptionBar::ToggleBarsEnabled(bool _new)
{
	for (int i = 0; i < bars.Num(); i++)
	{
		if (_new)
		{
			bars[i]->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			bars[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	lastChange = _new;
}

void UReceptionBar::CheckControllerBool()
{
	if (controller && lastChange != controller->isInService)
	{
		ToggleBarsEnabled(controller->isInService);
	}
}
