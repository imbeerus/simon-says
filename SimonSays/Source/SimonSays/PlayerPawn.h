// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class USimonButton;
class USoundWave;
class APlayerController;

UCLASS(hideCategories = ("Rendering", "Replication", "Actor", "Pawn"))
class SIMONSAYS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(TArray<USimonButton*> ButtonsToSet);

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void OnPlayerTurn();

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void OnChallangeTurn();

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void OnWrongButton(float TurnCount);

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void OnTimeIsOver(float TurnCount);

	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void ShowDefaultCursor();

	UFUNCTION(BlueprintCallable)
	void ShowHandCursor();

	UFUNCTION(BlueprintCallable) 
	void ShowChallengeSequence();

	UFUNCTION()
	void PlayChallengeButtons();

	UFUNCTION(BlueprintCallable, Category = "Turn")
	void AddToPlayerSequence(USimonButton* PressedButton);

	UFUNCTION(Category = "Timer")
	void CheckTimerValue();

	// Timer value for for beginning of the game
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Timer")
	float StartTimerValue = 60;

	// Countdown value
	UPROPERTY(BlueprintReadOnly, Category = "Timer")
	float TimerCount;

	UPROPERTY(BlueprintReadWrite, Category = "Turn")
	FString CurrentTurn;

	UPROPERTY(BlueprintReadOnly, Category = "Turn")
	int ScoreValue = 0;

	// Responsible for the fact that it is possible for a player to enter a sequence of buttons
	UPROPERTY(BlueprintReadOnly, Category = "Turn")
	bool IsInputEnabled;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	USoundWave* WinSound;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	USoundWave* LoseSound;

	// Delay between pressed buttons when chalange sequence is showed
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DelayBetweenButtonsPressed = 1.25f;

private:
	APlayerController* FirstPlayerController;
	TArray<USimonButton*> SequenceArray;
	TArray<USimonButton*> ButtonsArray;
	FTimerHandle CountdownHandle;
	FTimerHandle TurnHandle;
	float TurnCount = 0;

	void AddRandomButtonToSequence();
	void StopTimerCount();
	void StartTimerCount(float SecondsCount);
};
