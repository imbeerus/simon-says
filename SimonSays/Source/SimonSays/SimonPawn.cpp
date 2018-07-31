// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonPawn.h"
#include "SimonButton.h"
#include "TimerManager.h"
#include "Classes/Sound/SoundWave.h"
#include "Classes/GameFramework/PlayerController.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ASimonPawn::ASimonPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASimonPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASimonPawn::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// Called to bind functionality to input
void ASimonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {	Super::SetupPlayerInputComponent(PlayerInputComponent); }

void ASimonPawn::Initialise(TArray<USimonButton*> ButtonsToSet) { ButtonsArray = ButtonsToSet; }

void ASimonPawn::StartGame()
{
	ResetGameState();
	AddRandomButtonToSequence();
	ShowChallengeSequence();
}

void ASimonPawn::ResetGameState()
{
	TurnCount = 0;
	ScoreValue = 0;
	SequenceArray.Empty();
}

void ASimonPawn::AddRandomButtonToSequence() { SequenceArray.Add(ButtonsArray[FMath::RandRange(0.f, 4.f)]); }

void ASimonPawn::AddToPlayerSequence(USimonButton* PressedButton)
{
	if (IsInputEnabled && SequenceArray.Num() > 0)
	{
		if (LastPlayedButton != nullptr) LastPlayedButton->TurnOff();

		TurnCount++;
		bool IsSameButton = SequenceArray[TurnCount] == PressedButton;

		if (!IsSameButton)
		{
			PressedButton->Play(false); // Play button without sound
			if (LoseSound) {
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), LoseSound, GetActorLocation());
			}

			LastPlayedButton = nullptr;
			DisableSimonInput();
			StopTimerCount();
			OnWrongButton(ScoreValue);
			return;
		}
		else
		{
			LastPlayedButton = PressedButton;
			PressedButton->Play();
		}
		
		if (TurnCount == SequenceArray.Num() - 1)
		{
			ScoreValue++; // increase score value
			AddRandomButtonToSequence(); // add new random button to challange sequence
			ShowChallengeSequence(); // and show it
		}
	}
}

void ASimonPawn::ShowChallengeSequence()
{
	TurnCount = 0;
	DisableSimonInput();
	StopTimerCount();

	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("PlayChallengeButtons"));
	GetWorld()->GetTimerManager().SetTimer(TurnHandle, TimerDel, DelayBetweenButtonsPressed, true);
	OnChallangeTurn();
}

void ASimonPawn::PlayChallengeButtons()
{
	if (SequenceArray.Num() > 0)
	{
		SequenceArray[TurnCount]->Play();
		if (++TurnCount == SequenceArray.Num())
		{
			TurnCount = -1; // Because we need 0 at PlayButton
			EnableSimonInput();
			StartTimerCount();

			GetWorldTimerManager().ClearTimer(TurnHandle);
			OnPlayerTurn();
		}
	}
}

void ASimonPawn::StopTimerCount() {
	TimerCount = StartTimerValue;
	GetWorldTimerManager().ClearTimer(CountdownHandle);
}

void ASimonPawn::StartTimerCount()
{
	TimerCount = StartTimerValue;
	// Start countdown
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("CheckTimerValue"));
	GetWorld()->GetTimerManager().SetTimer(CountdownHandle, TimerDel, 1.f, true);
}

void ASimonPawn::CheckTimerValue()
{
	// Once we've called this function enough times, check count value
	if (--TimerCount <= 0)
	{
		DisableSimonInput();

		GetWorldTimerManager().ClearTimer(CountdownHandle);
		OnTimeIsOver(ScoreValue);
	}
}

void ASimonPawn::ShowDefaultCursor()
{
	GetWorld()->GetFirstPlayerController()->CurrentMouseCursor = EMouseCursor::Type::Default;
}
void ASimonPawn::ShowHandCursor() 
{ 
	GetWorld()->GetFirstPlayerController()->CurrentMouseCursor = EMouseCursor::Type::Hand;
}

void ASimonPawn::EnableSimonInput() { IsInputEnabled = true; }

void ASimonPawn::DisableSimonInput() { IsInputEnabled = false; }