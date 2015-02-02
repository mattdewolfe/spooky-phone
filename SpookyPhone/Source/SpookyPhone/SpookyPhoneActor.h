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
class SPOOKYPHONE_API ASpookyPhoneActor : public APawn
{
	GENERATED_BODY()

public:
	ASpookyPhoneActor(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;

private:

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void TogglePhone();

	UPROPERTY(VisibleDefaultsOnly, Category = StaticMesh)
	UStaticMeshComponent* m_phoneMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Material)
	UMaterial* m_phoneMaterial;

	UPROPERTY(VisibleDefaultsOnly, Category = StaticMesh)
	UStaticMeshComponent* m_screenMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Material)
	UMaterial* m_screenMaterial;

	UPROPERTY(VisibleDefaultsOnly, Category = UMG)
	UWidgetComponent* m_umgPhoneWidget;

	UPROPERTY(VisibleDefaultsOnly, Category = UMG)
	USpookyPhoneWidget* m_umgPhoneUI;

	UPROPERTY(VisibleDefaultsOnly, Category = Camera)
	UChildActorComponent* m_phoneCamera;

	int32 m_numApps;
};