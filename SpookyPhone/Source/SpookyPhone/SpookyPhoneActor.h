// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	UPROPERTY(VisibleDefaultsOnly, Category = StaticMesh)
	UStaticMeshComponent* m_phoneMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Material)
	UMaterial* m_phoneMaterial;

	UPROPERTY(VisibleDefaultsOnly, Category = StaticMesh)
	UStaticMeshComponent* m_screenMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Material)
	UMaterial* m_screenMaterial;

	int32 m_numApps;
};