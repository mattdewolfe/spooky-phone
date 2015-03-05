// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "SpookyPhoneAppWidget.generated.h"

UCLASS()
class SPOOKYPHONE_API USpookyPhoneAppWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void Construct_Implementation() override;

	UFUNCTION(BlueprintCallable, Category=UMG)
	virtual void OnAppClicked();

	void Select();
	void Unselect();

	UButton* AppButton;
	UTextBlock* AppText;

	FSlateBrush NormalStyle;
	FSlateBrush SelectedStyle;
};
