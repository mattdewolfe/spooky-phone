// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "CameraAppWidget.h"
#include "SpookyPawn.h"

void UCameraAppWidget::OnAppClicked()
{
	ASpookyPawn* SPawn = Cast<ASpookyPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (SPawn)
	{
		SPawn->Phone->ShowCamera();
	}
}