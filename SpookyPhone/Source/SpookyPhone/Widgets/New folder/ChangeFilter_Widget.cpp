// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "ChangeFilter_Widget.h"


void UChangeFilter_Widget::OnAppClicked()
{
	ASpookyPawn* sPawn = Cast<ASpookyPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (sPawn)
	{
		TEnumAsByte<FilterType> temp = sPawn->Phone->Camera->currentFilter;
		
		FString str;

		switch (temp)
		{
		case FilterType::VE_NIGHT:
			str = "night";
			temp = FilterType::VE_NORMAL;
			break;
		case FilterType::VE_NORMAL:
			str = "normal";
			temp = FilterType::VE_SPOOKY;
			break;
		case FilterType::VE_SPOOKY:
			str = "spooky";
			temp = FilterType::VE_NIGHT;
			break;
		default:
			temp = FilterType::VE_NORMAL;
			break;
		}

		GEngine->AddOnScreenDebugMessage(1002, 5, FColor::Blue, str);

		sPawn->Phone->Camera->SwitchFilter(temp);
		//and all is well. 
	}
}

//KW 