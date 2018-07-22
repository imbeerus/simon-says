// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "SimonButton.generated.h"

class UMaterial;
class USoundWave;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class SIMONSAYS_API USimonButton : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Materials")
	UMaterial* DefaultMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Materials")
	UMaterial* GlowMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	USoundWave* PlaySound;

	UFUNCTION(BlueprintCallable)
	void Play();

	UFUNCTION()
	void TurnOff();

	void TurnOn();

	float GetDuration();

private:
	FTimerHandle ButtonHandle;
};
