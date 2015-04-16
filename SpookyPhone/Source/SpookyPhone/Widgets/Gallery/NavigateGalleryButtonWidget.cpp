// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SpookyPawn.h"
#include "NavigateGalleryButtonWidget.h"

void UNavigateGalleryButtonWidget::Construct_Implementation()
{
	Super::Construct_Implementation();

	PictureSelected = 0;
	
	switch (Direction)
	{
	case Right:
		ButtonText->SetText(FText::FromString(TEXT("Next")));
		break;
	case Left:
		ButtonText->SetText(FText::FromString(TEXT("Prev")));
		break;
	}
}

void UNavigateGalleryButtonWidget::OnAppClicked()
{
	ASpookyPawn* SPawn = Cast<ASpookyPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (SPawn)
	{
		APhoneCamera* Camera = SPawn->Phone->Camera;
		NumPictures = Camera->numPictures;

		if (NumPictures <= 0)
			return;

		switch (Direction)
		{
		case Left:
			PictureSelected--;
			if (PictureSelected < 0)
			{
				PictureSelected = NumPictures - 1;
			}
			break;
		case Right:
			PictureSelected++;
			if (PictureSelected > NumPictures - 1)
			{
				PictureSelected = 0;
			}
			break;
		}

		SPawn->Phone->SetScreenMaterial(Camera->DisplayPicture(PictureSelected));
	}
}