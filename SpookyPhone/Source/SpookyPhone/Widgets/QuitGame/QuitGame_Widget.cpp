// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "QuitGame_Widget.h"
#include "SpookyPawn.h"

void UQuitGame_Widget::OnAppClicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("QUIT");
}

