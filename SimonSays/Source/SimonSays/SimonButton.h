// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PushableButton.h"
#include "SimonButton.generated.h"

class UMaterial;
class USoundWave;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class SIMONSAYS_API USimonButton : public UPushableButton
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Materials")
	UMaterial* DefaultMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Materials")
	UMaterial* GlowMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	USoundWave* PlaySound;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float Volume = 1.f;

	UFUNCTION(BlueprintCallable)
	void Play();

	void Play(bool IsWithSound);

	UFUNCTION()
	void TurnOff();

	void TurnOn();

	float GetDuration();

private:
	FTimerHandle ButtonHandle;
};
