// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "NavigateGalleryButtonWidget.h"

void UNavigateGalleryButtonWidget::Construct_Implementation()
{
	Super::Construct_Implementation();

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
	GalleryScreen->ChangePicture(Direction);
}