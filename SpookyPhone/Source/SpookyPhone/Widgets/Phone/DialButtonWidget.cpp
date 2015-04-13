// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "DialButtonWidget.h"

void UDialButtonWidget::Construct_Implementation()
{
	Super::Construct_Implementation();

	ButtonText->SetText(FText::AsNumber(Number));
}

void UDialButtonWidget::OnAppClicked()
{
	if (PhoneDisplay)
	{
		PhoneDisplay->AddNumber(Number);
	}
}