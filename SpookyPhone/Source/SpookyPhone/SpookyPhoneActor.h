// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpookyPhoneWidget.h"
#include "PhoneCamera.h"

#include "GameFramework/Actor.h"
#include "SpookyPhoneActor.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYPHONE_API ASpookyPhoneActor : public AActor
{
	GENERATED_BODY()

public:
	ASpookyPhoneActor(const FObjectInitializer& ObjectInitializer);

	void TogglePhone();
	void TogglePhoneUI();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleDefaultsOnly, Category = StaticMesh)
	UStaticMeshComponent* PhoneMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Material)
	UMaterial* PhoneMaterial;

	UPROPERTY(VisibleDefaultsOnly, Category = StaticMesh)
	UStaticMeshComponent* ScreenMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Material)
	UMaterial* ScreenMaterial;

	UPROPERTY(VisibleDefaultsOnly, Category = UMG)
	UWidgetComponent* UMGPhoneWidget;

	UPROPERTY(VisibleDefaultsOnly, Category = UMG)
	USpookyPhoneWidget* UMGPhoneUI;

	UPROPERTY(VisibleDefaultsOnly, Category = Camera)
	APhoneCamera* Camera;

	UPROPERTY()
	bool bIsHidden;
};