// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonButton.h"
#include "TimerManager.h"
#include "Classes/Materials/Material.h"
#include "Classes/Sound/SoundWave.h"
#include "Classes/Kismet/GameplayStatics.h"

void USimonButton::Play() { Play(true); }

void USimonButton::Play(bool IsWithSound) {
	// Clear blink timer
	GetWorld()->GetTimerManager().ClearTimer(BlinkHandle);
	IsBlinking = false;

	TurnOn();
	if (IsWithSound && PlaySound != nullptr) {
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

void USimonButton::Blink(float Duration)
{
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("SwitchState"));
	GetWorld()->GetTimerManager().SetTimer(BlinkHandle, TimerDel, Duration, true);
}

void USimonButton::SwitchState()
{
	if (IsBlinking)
	{
		SetMaterial(0, DefaultMaterial);
		IsBlinking = false;
	}
	else
	{
		SetMaterial(0, GlowMaterial);
		IsBlinking = true;
	}
}

float USimonButton::GetDuration()
{
	if (PlaySound == nullptr) { return 0.1f; }
	return PlaySound->Duration; 
}


