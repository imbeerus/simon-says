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
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Materials")
	UMaterial* ButtonElement;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Materials")
	UMaterial* ButtonGlowElement;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Setup")
	USoundWave* PlaySound;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	bool IsTurnedOn;

	UFUNCTION(BlueprintCallable)
	void TurnOn();

	UFUNCTION()
	void TurnOff();
private:

	void TurnOffWithDelay(float DelaySeconds);
};
