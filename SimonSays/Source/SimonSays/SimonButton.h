// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PushableButton.h"
#include "SimonButton.generated.h"

class UMaterial;
class USoundWave;
class UAudioComponent;

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
	USoundWave* SoundToPlay;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float Volume = 1.f;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UAudioComponent* AudioComponentToSet);

	UFUNCTION(BlueprintCallable)
	void Play(bool IsWithSound = true);

	UFUNCTION()
	void TurnOn();
	
	UFUNCTION(BlueprintCallable)
	void TurnOff();

	UFUNCTION(BlueprintCallable)
	void Blink(float Duration);
	
	UFUNCTION()
	void SwitchState();

	float GetDuration();

private:
	UAudioComponent* AudioComponent;
	FTimerHandle ButtonHandle;
	FTimerHandle BlinkHandle;
	bool IsBlinking = false;
};
