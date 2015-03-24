// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "UIWidget.h"
#include "Text.h"

void UUIWidget::Construct_Implementation()
{
	Super::Construct_Implementation();

	Button = (UButton*)GetWidgetFromName(TEXT("Button"));
	ButtonText = (UTextBlock*)GetWidgetFromName(TEXT("ButtonText"));

	NormalStyle = Button->WidgetStyle.Normal;
	SelectedStyle = Button->WidgetStyle.Hovered;
}

void UUIWidget::OnAppClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Button Clicked"));
}

void UUIWidget::Select()
{
	Button->WidgetStyle.SetNormal(SelectedStyle);
}

void UUIWidget::Unselect()
{
	Button->WidgetStyle.SetNormal(NormalStyle);
}