// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/UIWidget.h"
#include "Widgets/Phone/PhoneDisplayWidget.h"
#include "PhoneCallButtonWidget.generated.h"

UENUM(BlueprintType)
enum class EPhoneAction : uint8
{
	CALL		UMETA(DisplayName = "Call"),
	HANGUP		UMETA(DisplayName = "Hangup")
};

UCLASS()
class SPOOKYPHONE_API UPhoneCallButtonWidget : public UUIWidget
{
	GENERATED_BODY()
	
public:
	virtual void Construct_Implementation() override;
	virtual void OnAppClicked() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Phone)
	UPhoneDisplayWidget* PhoneDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Phone)
	TEnumAsByte<EPhoneAction> PhoneAction;

private:
	virtual void CheckNumber(FString PhoneNumber);
};