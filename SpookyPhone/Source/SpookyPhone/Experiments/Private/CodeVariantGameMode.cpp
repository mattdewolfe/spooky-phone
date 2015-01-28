// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "CodeVariant.h"
#include "CodeVariantGameMode.h"
#include "CodeVariantHUD.h"
#include "IDMobileCharacter.h"
#include "IDMobileController.h"

ACodeVariantGameMode::ACodeVariantGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	DefaultPawnClass = AIDMobileCharacter::StaticClass();
	PlayerControllerClass = AIDMobileController::StaticClass();

	//HUDClass = ACodeVariantHUD::StaticClass();
}
