// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "UIWidget.h"
#include "Text.h"

void UUIWidget::Construct_Implementation()
{
	Super::Construct_Implementation();

	AppButton = (UButton*)GetWidgetFromName(TEXT("AppButton"));
	AppText = (UTextBlock*)GetWidgetFromName(TEXT("AppText"));

	NormalStyle = AppButton->WidgetStyle.Normal;
	SelectedStyle = AppButton->WidgetStyle.Hovered;
}

void UUIWidget::OnAppClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Button Clicked"));
}

void UUIWidget::Select()
{
	AppButton->WidgetStyle.SetNormal(SelectedStyle);
}

void UUIWidget::Unselect()
{
	AppButton->WidgetStyle.SetNormal(NormalStyle);
}