// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "HomeButtonWidget.h"
#include "SpookyPawn.h"

void UHomeButtonWidget::OnAppClicked()
{
	ASpookyPawn* SPawn = Cast<ASpookyPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (SPawn)
	{
		SPawn->Phone->GoHome();
	}
}