// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpookyPhoneAppWidget.h"
#include "CameraAppWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API UCameraAppWidget : public USpookyPhoneAppWidget
{
	GENERATED_BODY()
	
public:
	virtual void OnAppClicked();
};
