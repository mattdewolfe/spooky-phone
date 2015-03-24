// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UIWidget.h"
#include "HomeButtonWidget.generated.h"

/**
*
*/
UCLASS()
class SPOOKYPHONE_API UHomeButtonWidget : public UUIWidget
{
	GENERATED_BODY()

public:
	virtual void OnAppClicked();
};
