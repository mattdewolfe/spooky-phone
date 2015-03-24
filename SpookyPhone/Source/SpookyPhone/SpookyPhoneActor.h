// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/ScreenWidget.h"
#include "PhoneCamera.h"
#include "Widgets/HomeButtonWidget.h"

#include "GameFramework/Actor.h"
#include "SpookyPhoneActor.generated.h"

UENUM()
enum EScreens
{
	HOME,
	CAMERA
};

UCLASS()
class SPOOKYPHONE_API ASpookyPhoneActor : public AActor
{
	GENERATED_BODY()

public:
	ASpookyPhoneActor(const FObjectInitializer& ObjectInitializer);

	void TogglePhone();
	void GoToScreen(EScreens Screen);

	void ShowCamera();
	void GoHome();

	void NavigateByDirection(ENavigationDirection Direction);
	void Select();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

private:
	// Phone mesh and material
	UPROPERTY(VisibleDefaultsOnly, Category = StaticMesh)
	UStaticMeshComponent* PhoneMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Material)
	UMaterial* PhoneMaterial;


	// Background for screen
	UPROPERTY(VisibleDefaultsOnly, Category = StaticMesh)
	UStaticMeshComponent* ScreenMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Material)
	UMaterial* ScreenMaterial;


	// Phone screens
	TSubclassOf<class AActor> PhoneWidgetBlueprint;

	UPROPERTY(VisibleDefaultsOnly, Category = UMG)
	AActor* PhoneUI;

	UPROPERTY(VisibleDefaultsOnly, Category = UMG)
	UWidgetComponent* UMGPhoneHomeWidget;

	UPROPERTY(VisibleDefaultsOnly, Category = UMG)
	UHomeButtonWidget* UMGHomeButton;


	//UPROPERTY(VisibleDefaultsOnly, Category = UMG)
	//UWidgetComponent* UMGPhoneScreenWidget;

	//UPROPERTY(VisibleDefaultsOnly, Category = UMG)
	//UScreenWidget* UMGPhoneScreen;


	// Maps of screens
	UPROPERTY(VisibleDefaultsOnly, Category = UMG)
	TArray<UWidgetComponent*> ScreenWidgetComponents;
	UPROPERTY(VisibleDefaultsOnly, Category = UMG)
	TArray<UScreenWidget*> ScreenWidgets;

	// Camera
	UPROPERTY(VisibleDefaultsOnly, Category = Camera)
	APhoneCamera* Camera;

	EScreens CurrentScreen;

	UPROPERTY()
	bool bIsHidden;
};