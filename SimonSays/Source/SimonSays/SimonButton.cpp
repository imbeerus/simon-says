// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonButton.h"
#include "TimerManager.h"
#include "Classes/Materials/Material.h"
#include "Classes/Sound/SoundWave.h"
#include "Classes/Kismet/GameplayStatics.h"

void USimonButton::Play() {
	TurnOn();
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("TurnOff"));
	GetWorld()->GetTimerManager().SetTimer(ButtonHandle, TimerDel, GetDuration(), false);
}

void USimonButton::TurnOn()
{
	SetMaterial(0, GlowMaterial);
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		PlaySound,
		GetComponentLocation()
	);
}

void USimonButton::TurnOff() {
	SetMaterial(0, DefaultMaterial); 
	GetWorld()->GetTimerManager().ClearTimer(ButtonHandle);
}

float USimonButton::GetDuration() {	return PlaySound->Duration; }