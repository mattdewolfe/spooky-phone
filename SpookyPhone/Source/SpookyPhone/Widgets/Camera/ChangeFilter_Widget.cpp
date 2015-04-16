// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "ChangeFilter_Widget.h"


void UChangeFilter_Widget::OnAppClicked()
{
	ASpookyPawn* sPawn = Cast<ASpookyPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (sPawn)
	{
		TEnumAsByte<FilterType> temp = sPawn->Phone->Camera->currentFilter;
		
		switch (temp)
		{
		case FilterType::VE_NIGHT:
			temp = FilterType::VE_NORMAL;
			break;
		case FilterType::VE_NORMAL:
			temp = FilterType::VE_SPOOKY;
			break;
		case FilterType::VE_SPOOKY:
			temp = FilterType::VE_NIGHT;
			break;
		default:
			temp = FilterType::VE_NORMAL;
			break;
		}

		sPawn->Phone->Camera->SwitchFilter(temp);
		//and all is well. 
	}
}

//KW 