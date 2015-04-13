// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "AppWidget.h"

void UAppWidget::OnAppClicked()
{
	ASpookyPawn* SPawn = Cast<ASpookyPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (SPawn)
	{
		SPawn->Phone->GoToScreen(AppScreen);
	}
}