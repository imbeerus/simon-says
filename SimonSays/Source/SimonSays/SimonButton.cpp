// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonButton.h"
#include "Classes/Materials/Material.h"
#include "Classes/Sound/SoundWave.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TimerManager.h"

void USimonButton::TurnOn()
{
	SetMaterial(0, ButtonGlowElement);
	IsTurnedOn = true;
	UE_LOG(LogTemp, Display, TEXT("%s is turned on"), *GetOwner()->GetName());
	TurnOffWithDelay(PlaySound->Duration);
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		PlaySound,
		GetComponentLocation()
	);
}

void USimonButton::TurnOff()
{
	SetMaterial(0, ButtonElement);
	IsTurnedOn = false;
	UE_LOG(LogTemp, Display, TEXT("%s is turned off"), *GetOwner()->GetName());
}

void USimonButton::TurnOffWithDelay(float DelaySeconds)
{
	// TODO: Add delay
	UE_LOG(LogTemp, Display, TEXT("%f delay"), DelaySeconds);
}
