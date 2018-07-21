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

void APlayerPawn::Initialise(TArray<USimonButton*> ButtonsToSet) { ButtonsArray = ButtonsToSet; }

void APlayerPawn::StartGame()
{
	// TODO: Add check ButtonsArray

	// Adding random button to sequence
	ResetGame();
	ShowChallengeSequence();
}

void APlayerPawn::ResetGame()
{
	TurnCount = 0;
	SequenceArray.Empty();
	AddRandomButtonToSequence();
}

void APlayerPawn::EnablePlayerInput() { FirstPlayerController->bEnableClickEvents = true; }

void APlayerPawn::DisablePlayerInput() { FirstPlayerController->bEnableClickEvents = false; }

void APlayerPawn::ShowDefaultCursor() { FirstPlayerController->CurrentMouseCursor = EMouseCursor::Type::Default; }

void APlayerPawn::ShowHandCursor() { FirstPlayerController->CurrentMouseCursor = EMouseCursor::Type::Hand; }

void APlayerPawn::AddRandomButtonToSequence() { SequenceArray.Add(ButtonsArray[FMath::RandRange(0.f, 4.f)]); }

void APlayerPawn::PlayButton(USimonButton* ButtonToPlay) {
	ButtonToPlay->TurnOn();
	IsSomeButtonPlaying = true;
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("TurnOffButton"), ButtonToPlay);
	GetWorld()->GetTimerManager().SetTimer(ButtonHandle, TimerDel, ButtonToPlay->GetDuration(), false);
}

void APlayerPawn::AddToPlayerSequence(USimonButton* PressedButton)
{
	TurnCount++;
	bool IsSameButton = SequenceArray[TurnCount] == PressedButton;

	if (!IsSameButton)
	{
		// Game over
	} 
	else if (IsSameButton && TurnCount == SequenceArray.Num())
	{
		AddRandomButtonToSequence();
		ShowChallengeSequence();
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
	// DisablePlayerInput();

	TurnCount = 0;
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("PlayChallengeButtons"));
	GetWorld()->GetTimerManager().SetTimer(TurnHandle, TimerDel, 1.f, true); // Test
}

void APlayerPawn::PlayChallengeButtons()
{
	PlayButton(SequenceArray[TurnCount]);
	if (++TurnCount == SequenceArray.Num())
	{
		TurnCount = -1; // Because we need 0 at PlayButton
		StartTimerCount(StartTimerValue);
		EnablePlayerInput();

		GetWorldTimerManager().ClearTimer(TurnHandle);
	}
}

void APlayerPawn::StopTimerCount() {
	TimerCount = StartTimerValue; 
	GetWorldTimerManager().ClearTimer(CountdownHandle);
}

void APlayerPawn::StartTimerCount(float SecondsCount)
{
	TimerCount = SecondsCount;

	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("CheckTimerValue"));
	GetWorld()->GetTimerManager().SetTimer(CountdownHandle, TimerDel, 1.f, true);
}

void APlayerPawn::CheckTimerValue()
{
	UE_LOG(LogTemp, Warning, TEXT("Count value: %f"), TimerCount);
	// Once we've called this function enough times, check count value
	if (--TimerCount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time is over"));
		GetWorldTimerManager().ClearTimer(CountdownHandle);
	}
}