// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "SimonButton.h"
#include "TimerManager.h"
#include "Classes/Sound/SoundWave.h"
#include "Classes/GameFramework/PlayerController.h"
#include "Math/UnrealMathUtility.h"

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
	TurnCount = 0;
	FirstPlayerController = GetWorld()->GetFirstPlayerController();
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

void APlayerPawn::Initialise(TArray<USimonButton*> ButtonsToSet)
{
	ButtonsArray = ButtonsToSet;
}

void APlayerPawn::StartGame()
{
	StartTimerCount(StartTimerValue);
}

void APlayerPawn::ResetGame()
{
	TurnCount = 0;
}

void APlayerPawn::EnablePlayerInput() { FirstPlayerController->bEnableClickEvents = false; }
void APlayerPawn::DisablePlayerInput() { FirstPlayerController->bEnableClickEvents = true; }

void APlayerPawn::GameOver()
{
	// GetWorld()->GetTimerManager().ClearTimer(CountdownHandle);
}

void APlayerPawn::ShowDefaultCursor() { FirstPlayerController->CurrentMouseCursor = EMouseCursor::Type::Default; }
void APlayerPawn::ShowHandCursor() { FirstPlayerController->CurrentMouseCursor = EMouseCursor::Type::Hand; }

void APlayerPawn::PlayButton(USimonButton* ButtonToPlay) { PlayButton(ButtonToPlay, true); }

void APlayerPawn::PlayButton(USimonButton* ButtonToPlay, bool IsPlayer)
{
	if (IsPlayer)
	{
		IsSomeButtonPlaying = true;
		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("TurnOffButton"), ButtonToPlay);
		GetWorld()->GetTimerManager().SetTimer(ButtonHandle, TimerDel, ButtonToPlay->GetDuration(), false);
		ButtonToPlay->TurnOn();
	}
}

void APlayerPawn::AddToPlayerSequence(USimonButton* PressedButton)
{
	TurnCount++;
	if (ButtonsArray[TurnCount] != PressedButton)
	{
		GameOver();
	}
}

void APlayerPawn::TurnOffButton(USimonButton* SimonButton)
{
	IsSomeButtonPlaying = false;
	SimonButton->TurnOff();
	GetWorld()->GetTimerManager().ClearTimer(ButtonHandle);
}

void APlayerPawn::ShowChallengeSequence()
{
	// USimonButton* RandomButton = ButtonsArray[FMath::RandRange(0, 4)];
	// SequenceArray.Add(RandomButton);

	// Play buttons every second
}

void APlayerPawn::ResetTimerCount() { TimerCount = StartTimerValue; }

void APlayerPawn::StartTimerCount(float SecondsCount)
{
	TimerCount = SecondsCount;

	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("CheckTimerValue"));
	GetWorld()->GetTimerManager().SetTimer(CountdownHandle, TimerDel, 1.f, true);
}

void APlayerPawn::CheckTimerValue()
{
	// Once we've called this function enough times, check count value
	if (--TimerCount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time is over"));
		GetWorldTimerManager().ClearTimer(CountdownHandle);
	}
	UE_LOG(LogTemp, Warning, TEXT("Count value: %f"), TimerCount);
}