// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "PhoneCallButtonWidget.h"
#include "SpookyPawn.h"

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
	FString Number = "402-6647";

	if (PhoneNumber == Number)
	{
		ASpookyPawn* temp = Cast<ASpookyPawn>(GetOwningPlayer()->GetPawn());
		temp->FlagForVictory();
	}
}