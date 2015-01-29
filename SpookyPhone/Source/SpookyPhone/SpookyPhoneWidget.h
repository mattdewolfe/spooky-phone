// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "SpookyPhoneWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API USpookyPhoneWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleDefaultsOnly)
	int32 m_apps;
};