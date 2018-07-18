// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "SimonButton.h"
#include "TimerManager.h"
#include "Classes/GameFramework/PlayerController.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	// Display StartTimerValue
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPawn::ShowDefaultCursor()
{
	GetWorld()->GetFirstPlayerController()->CurrentMouseCursor = EMouseCursor::Type::Default;
}

void APlayerPawn::ShowHandCursor()
{
	GetWorld()->GetFirstPlayerController()->CurrentMouseCursor = EMouseCursor::Type::Hand;
}

void APlayerPawn::PlayButton(USimonButton* ButtonToPlay)
{
	IsSomeButtonPlaying = true;
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("TurnOffButton"), ButtonToPlay);
	GetWorld()->GetTimerManager().SetTimer(ButtonTimerHandle, TimerDel, ButtonToPlay->GetDuration(), false);
	ButtonToPlay->TurnOn();
}

void APlayerPawn::TurnOffButton(USimonButton* SimonButton)
{
	IsSomeButtonPlaying = false;
	SimonButton->TurnOff();
	GetWorld()->GetTimerManager().ClearTimer(ButtonTimerHandle);
}

void APlayerPawn::StartTimerCount()
{
	StartTimerCount(StartTimerValue);
}

void APlayerPawn::StartTimerCount(float SecondsCount)
{
	TimerCount = SecondsCount;

	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("CheckTimerValue"));
	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, TimerDel, 1.f, true);
}

void APlayerPawn::CheckTimerValue()
{
	// Once we've called this function enough times, check count value
	// if (--TimerCount <= 0 && IsRightInputSequence)
	if (--TimerCount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time is over"));
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	}
	UE_LOG(LogTemp, Warning, TEXT("Count value: %f"), TimerCount);
}
