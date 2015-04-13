// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "PhoneCallButtonWidget.h"

void UPhoneCallButtonWidget::Construct_Implementation()
{
	Super::Construct_Implementation();
}

void UPhoneCallButtonWidget::OnAppClicked()
{
	switch (PhoneAction)
	{
	case EPhoneAction::CALL:
		CheckNumber(PhoneDisplay->GetNumber());
		break;
	case EPhoneAction::HANGUP:
		PhoneDisplay->RemoveNumber();
		break;
	}
}

void UPhoneCallButtonWidget::CheckNumber(FString PhoneNumber)
{
	FString Number = "(416) 724-3141";

	if (PhoneNumber == Number)
	{
		// fire some event
		UE_LOG(LogTemp, Warning, TEXT("Number dialed!"));
	}
}