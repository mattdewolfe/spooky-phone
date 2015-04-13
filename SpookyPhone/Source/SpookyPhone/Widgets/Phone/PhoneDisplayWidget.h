// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "PhoneDisplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API UPhoneDisplayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void Construct_Implementation() override;
	void ClearNumber();

	void RemoveNumber();
	void AddNumber(int32 Number);

	FString GetNumber();

private:
	FString PhoneNumber;

	int32 NumberLength;

	UTextBlock* DisplayText;
};
