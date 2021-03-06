// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/UIWidget.h"
#include "Widgets/Phone/PhoneDisplayWidget.h"
#include "DialButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API UDialButtonWidget : public UUIWidget
{
	GENERATED_BODY()
	
public:
	virtual void Construct_Implementation() override;
	virtual void OnAppClicked() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Phone)
	int32 Number;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Phone)
	UPhoneDisplayWidget* PhoneDisplay;
};
