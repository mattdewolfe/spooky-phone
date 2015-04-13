// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "Widgets/Phone/PhoneCallButtonWidget.h"
#include "PhoneScreenWidget.h"

void UPhoneScreenWidget::Construct_Implementation()
{
	Super::Construct_Implementation();

	PhoneDisplay = (UPhoneDisplayWidget*)GetWidgetFromName(TEXT("PhoneDisplay"));

	((UPhoneCallButtonWidget*)GetWidgetFromName(TEXT("CallButton")))->PhoneDisplay = PhoneDisplay;
	((UPhoneCallButtonWidget*)GetWidgetFromName(TEXT("HangupButton")))->PhoneDisplay = PhoneDisplay;

	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);

	for (UWidget* Widget : Widgets)
	{
		UDialButtonWidget* DialButton = Cast<UDialButtonWidget>(Widget);
		if (DialButton)
		{
			DialButton->PhoneDisplay = PhoneDisplay;
		}
	}
}