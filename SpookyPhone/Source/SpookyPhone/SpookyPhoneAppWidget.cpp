// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SpookyPhoneAppWidget.h"
#include "Text.h"

void USpookyPhoneAppWidget::Construct_Implementation()
{
	Super::Construct_Implementation();

	AppButton = (UButton*)GetWidgetFromName(TEXT("AppButton"));
	AppText = (UTextBlock*)GetWidgetFromName(TEXT("AppText"));

	NormalStyle = AppButton->WidgetStyle.Normal;
	SelectedStyle = AppButton->WidgetStyle.Hovered;
}

void USpookyPhoneAppWidget::OnAppClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Button Clicked"));
}

void USpookyPhoneAppWidget::Select()
{
	AppButton->WidgetStyle.SetNormal(SelectedStyle);
}

void USpookyPhoneAppWidget::Unselect()
{
	AppButton->WidgetStyle.SetNormal(NormalStyle);
}