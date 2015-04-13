// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/UIWidget.h"
#include "SpookyPawn.h"
#include "AppWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API UAppWidget : public UUIWidget
{
	GENERATED_BODY()
	
public:
	virtual void OnAppClicked();

	UPROPERTY(EditAnywhere, Category = App)
	TEnumAsByte<EScreens> AppScreen;
};
