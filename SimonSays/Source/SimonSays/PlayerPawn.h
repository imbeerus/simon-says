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

	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void ResetGame();

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

	UPROPERTY(BlueprintReadOnly, Category = "Turn")
	bool IsInputEnabled;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	USoundWave* WinSound;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	USoundWave* LoseSound;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DelayBetweenButtonsPressed = 1.25f;

private:
	APlayerController* FirstPlayerController;
	TArray<USimonButton*> SequenceArray;
	TArray<USimonButton*> ButtonsArray;
	FTimerHandle CountdownHandle;
	FTimerHandle TurnHandle;
	float TurnCount;
	float TimerCount;

	void AddRandomButtonToSequence();
	void StopTimerCount();
	void StartTimerCount(float SecondsCount);
};
