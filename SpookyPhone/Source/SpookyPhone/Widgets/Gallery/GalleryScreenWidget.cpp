// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "Widgets/Phone/PhoneCallButtonWidget.h"
#include "Widgets/Gallery/NavigateGalleryButtonWidget.h"
#include "GalleryScreenWidget.h"
#include "SpookyPawn.h"

void UGalleryScreenWidget::Construct_Implementation()
{
	Super::Construct_Implementation();

	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);

	for (UWidget* Widget : Widgets)
	{
		UNavigateGalleryButtonWidget* NavigateButton = Cast<UNavigateGalleryButtonWidget>(Widget);
		if (NavigateButton)
		{
			NavigateButton->GalleryScreen = this;
		}
	}
}

void UGalleryScreenWidget::Open()
{
	ASpookyPawn* SPawn = Cast<ASpookyPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (SPawn)
	{
		APhoneCamera* Camera = SPawn->Phone->Camera;
		NumPictures = Camera->numPictures;

		if (NumPictures > 0)
			SPawn->Phone->SetScreenMaterial(Camera->DisplayPicture(PictureSelected));
	}
}

void UGalleryScreenWidget::ChangePicture(TEnumAsByte<ENavigationDirection> Direction)
{
	ASpookyPawn* SPawn = Cast<ASpookyPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (SPawn)
	{
		APhoneCamera* Camera = SPawn->Phone->Camera;
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