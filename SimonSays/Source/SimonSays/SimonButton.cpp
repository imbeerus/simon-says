// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonButton.h"
#include "Classes/Materials/Material.h"
#include "Classes/Sound/SoundWave.h"
#include "Classes/Kismet/GameplayStatics.h"

void USimonButton::TurnOn()
{
	SetMaterial(0, GlowMaterial);
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		PlaySound,
		GetComponentLocation()
	);
}

void USimonButton::TurnOff() { SetMaterial(0, DefaultMaterial); }

float USimonButton::GetDuration() {	return PlaySound->Duration; }