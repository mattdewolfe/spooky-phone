// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/UIWidget.h"
#include "NavigateGalleryButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API UNavigateGalleryButtonWidget : public UUIWidget
{
	GENERATED_BODY()
	
public:
	virtual void Construct_Implementation() override;
	virtual void OnAppClicked() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gallery)
	TEnumAsByte<ENavigationDirection> Direction;

	int32 PictureSelected;
	int32 NumPictures;
};