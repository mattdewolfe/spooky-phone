// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/UIWidget.h"
#include "SnapPictureButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API USnapPictureButtonWidget : public UUIWidget
{
	GENERATED_BODY()
	
public:
	virtual void OnAppClicked();
};
