// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "SPInGameClock.generated.h"

UCLASS()
class SPOOKYPHONE_API ASPInGameClock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPInGameClock(const FObjectInitializer& _init);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Rendering)
	TArray<UMaterial*> clockFrames;

	UStaticMesh* baseMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mesh)
	UStaticMeshComponent* minutesSM;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mesh)
	UStaticMeshComponent* powerOf10SecondsSM;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mesh)
	UStaticMeshComponent* secondsSM;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mesh)
	UStaticMeshComponent* semicolonSM;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Timer)
	float timeToPlay;

	UFUNCTION(BlueprintCallable, Category = Timer)
	float GetTimeRemainingInGame();

private:
	uint32 currentMinuteTime;
	uint32 currentPower10SecondTime;
	uint32 currentSecondTime;

	float timeRemaining;
	
	void UpdateClock();
	void SetSeconds(uint32 _val);
	void SetMinutes(uint32 _val);
	void SetPower10Seconds(uint32 _val);

};
