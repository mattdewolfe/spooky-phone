// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/ScreenWidget.h"
#include "GalleryScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API UGalleryScreenWidget : public UScreenWidget
{
	GENERATED_BODY()
	
public:
	void Construct_Implementation() override;

	void Open() override;

	void ChangePicture(TEnumAsByte<ENavigationDirection> Direction);

	int32 PictureSelected;
	int32 NumPictures;
};
