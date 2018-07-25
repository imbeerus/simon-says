// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonButton.h"
#include "TimerManager.h"
#include "Classes/Materials/Material.h"
#include "Classes/Sound/SoundWave.h"
#include "Classes/Kismet/GameplayStatics.h"

void USimonButton::Play() {	Play(true); }

void USimonButton::Play(bool IsWithSound) {
	TurnOn();
	if (IsWithSound) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PlaySound, GetComponentLocation(), Volume);
	}
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("TurnOff"));
	GetWorld()->GetTimerManager().SetTimer(ButtonHandle, TimerDel, GetDuration(), false);
}

void USimonButton::TurnOn()
{
	Push();
	SetMaterial(0, GlowMaterial);
}

void USimonButton::TurnOff() {
	UnPush();
	SetMaterial(0, DefaultMaterial);
	GetWorld()->GetTimerManager().ClearTimer(ButtonHandle);
}

float USimonButton::GetDuration() { return PlaySound->Duration; }