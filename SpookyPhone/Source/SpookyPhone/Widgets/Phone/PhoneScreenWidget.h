// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/ScreenWidget.h"
#include "Widgets/Phone/DialButtonWidget.h"
#include "Widgets/Phone/PhoneDisplayWidget.h"
#include "PhoneScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API UPhoneScreenWidget : public UScreenWidget
{
	GENERATED_BODY()
	
public:
	void Construct_Implementation() override;

private:
	UPhoneDisplayWidget* PhoneDisplay;
};
