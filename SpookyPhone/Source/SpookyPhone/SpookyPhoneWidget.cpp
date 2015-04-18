// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SpookyPhoneWidget.h"

FEventReply USpookyPhoneWidget::OnKeyDown_Implementation(FGeometry MyGeometry, FKeyboardEvent InKeyboardEvent)
{
	if (bLockControls)
	{
		FEventReply Reply;
		Reply.NativeReply = FReply::Handled();
		return Reply;
	}
	else if (InKeyboardEvent.GetKey() == EKeys::Right)
	{
		SelectNextApp();

		FEventReply Reply;
		Reply.NativeReply = FReply::Handled();
		return Reply;
	}
	else
	{
		return Super::OnKeyDown_Implementation(MyGeometry, InKeyboardEvent);
	}
}

void USpookyPhoneWidget::Construct_Implementation()
{
	Super::Construct_Implementation();
}

void AddButton()
{
	
}

void USpookyPhoneWidget::SelectNextApp()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("next app!")));
	}
}