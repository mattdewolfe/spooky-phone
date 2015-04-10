// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/UIWidget.h"
#include "QuitGame_Widget.generated.h"

UCLASS()
class SPOOKYPHONE_API UQuitGame_Widget : public UUIWidget
{
	GENERATED_BODY()

public:
	virtual void OnAppClicked();
};

