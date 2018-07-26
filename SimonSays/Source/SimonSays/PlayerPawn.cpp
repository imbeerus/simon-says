// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "SimonButton.h"
#include "TimerManager.h"
#include "Classes/Sound/SoundWave.h"
#include "Classes/GameFramework/PlayerController.h"
#include "Classes/Kismet/GameplayStatics.h"
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
	IsInputEnabled = false;
	FirstPlayerController = GetWorld()->GetFirstPlayerController();
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
	TurnCount = 0;
	SequenceArray.Empty();
	AddRandomButtonToSequence();
	ShowChallengeSequence();
}

void APlayerPawn::ShowDefaultCursor() { FirstPlayerController->CurrentMouseCursor = EMouseCursor::Type::Default; }

void APlayerPawn::ShowHandCursor() { FirstPlayerController->CurrentMouseCursor = EMouseCursor::Type::Hand; }

void APlayerPawn::AddRandomButtonToSequence() { SequenceArray.Add(ButtonsArray[FMath::RandRange(0.f, 4.f)]); }

void APlayerPawn::AddToPlayerSequence(USimonButton* PressedButton)
{
	if (SequenceArray.Num() > 0)
	{
		TurnCount++;
		bool IsSameButton = SequenceArray[TurnCount] == PressedButton;
		if (IsSameButton) {
			PressedButton->Play();
		}
		else {
			PressedButton->Play(false); // Play button without sound
			if (LoseSound) {
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), LoseSound, GetActorLocation());
			}
			OnWrongButton(TurnCount);
			IsInputEnabled = false;
			return;
		}

		//  If last button was guessed then
		if (IsSameButton && (TurnCount == SequenceArray.Num() - 1)) {
			AddRandomButtonToSequence(); // add new random button to challange sequence
			ShowChallengeSequence(); // and show it
		}
	}
}

void APlayerPawn::ShowChallengeSequence()
{
	OnChallangeTurn();

	IsInputEnabled = false;
	TurnCount = 0;
	StopTimerCount();

	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("PlayChallengeButtons"));
	GetWorld()->GetTimerManager().SetTimer(TurnHandle, TimerDel, DelayBetweenButtonsPressed, true);
}

void APlayerPawn::PlayChallengeButtons()
{
	if (SequenceArray.Num() > 0)
	{
		SequenceArray[TurnCount]->Play();
		if (++TurnCount == SequenceArray.Num())
		{
			OnPlayerTurn();

			IsInputEnabled = true;
			TurnCount = -1; // Because we need 0 at PlayButton
			StartTimerCount(StartTimerValue); // Start countdow for player turn
			GetWorldTimerManager().ClearTimer(TurnHandle);
		}
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
	// Once we've called this function enough times, check count value
	if (--TimerCount <= 0)
	{
		OnTimeIsOver(TurnCount);
		IsInputEnabled = false;
		GetWorldTimerManager().ClearTimer(CountdownHandle);
	}
}