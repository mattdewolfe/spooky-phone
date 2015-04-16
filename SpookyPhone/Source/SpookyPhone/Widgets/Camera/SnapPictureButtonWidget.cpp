// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SnapPictureButtonWidget.h"
#include "SpookyPawn.h"

void USnapPictureButtonWidget::OnAppClicked()
{
	ASpookyPawn* SPawn = Cast<ASpookyPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (SPawn)
	{
		SPawn->Phone->Camera->TakePicture();
	}
}