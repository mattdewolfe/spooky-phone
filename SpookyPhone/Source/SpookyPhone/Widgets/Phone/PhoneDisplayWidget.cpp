// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "PhoneDisplayWidget.h"

void UPhoneDisplayWidget::Construct_Implementation()
{
	Super::Construct_Implementation();

	DisplayText = (UTextBlock*)GetWidgetFromName(TEXT("DisplayText"));

	NumberLength = 0;
}

void UPhoneDisplayWidget::ClearNumber()
{
	NumberLength = 0;
	PhoneNumber.Empty();

	DisplayText->SetText(FText::FromString(PhoneNumber));
}

void UPhoneDisplayWidget::AddNumber(int32 Number)
{
	if (NumberLength == 10)
		return;

	if (NumberLength == 3)
	{
		PhoneNumber.AppendChar('-');
	}
	else if (NumberLength == 7)
	{
		PhoneNumber.InsertAt(0, '(');
		PhoneNumber = PhoneNumber.Replace(TEXT("-"), TEXT(") "));

		PhoneNumber.InsertAt(9, '-');
	}
	PhoneNumber.AppendInt(Number);

	NumberLength++;

	DisplayText->SetText(FText::FromString(PhoneNumber));
}

void UPhoneDisplayWidget::RemoveNumber()
{
	if (NumberLength == 0)
		return;

	PhoneNumber.RemoveAt(PhoneNumber.Len() - 1);
	if (NumberLength == 4)
	{
		PhoneNumber.RemoveAt(PhoneNumber.Len() - 1);
	}
	else if (NumberLength == 8)
	{
		PhoneNumber.RemoveAt(9);
		PhoneNumber = PhoneNumber.Replace(TEXT(") "), TEXT("-"));

		PhoneNumber.RemoveAt(0);
	}

	NumberLength--;

	DisplayText->SetText(FText::FromString(PhoneNumber));
}

FString UPhoneDisplayWidget::GetNumber()
{
	return PhoneNumber;
}