// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonButton.h"
#include "Engine/World.h"
#include "Classes/Materials/Material.h"
#include "Classes/Sound/SoundWave.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TimerManager.h"

void USimonButton::TurnOn()
{
	SetMaterial(0, ButtonGlowElement);
	IsTurnedOn = true;
	UE_LOG(LogTemp, Display, TEXT("%s is turned on"), *GetOwner()->GetName());
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		PlaySound,
		GetComponentLocation()
	);
	TurnOffWithDelay(PlaySound->Duration);
}

void USimonButton::TurnOff()
{
	SetMaterial(0, ButtonElement);
	IsTurnedOn = false;
	UE_LOG(LogTemp, Display, TEXT("%s is turned off"), *GetOwner()->GetName());
}

void USimonButton::TurnOffWithDelay(float DelaySeconds)
{
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("TurnOff"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, DelaySeconds, false);
}
