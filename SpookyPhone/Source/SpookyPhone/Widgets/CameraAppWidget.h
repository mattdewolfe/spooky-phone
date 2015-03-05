// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UIWidget.h"
#include "CameraAppWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API UCameraAppWidget : public UUIWidget
{
	GENERATED_BODY()
	
public:
	virtual void OnAppClicked();
};
