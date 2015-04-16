// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/UIWidget.h"
#include "SpookyPawn.h"
#include "PhoneCamera.h"
#include "ChangeFilter_Widget.generated.h"

UCLASS()
class SPOOKYPHONE_API UChangeFilter_Widget : public UUIWidget
{
	GENERATED_BODY()

public: 
	virtual void OnAppClicked();

};
