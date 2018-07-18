// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class USimonButton;
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

	UFUNCTION(BlueprintCallable)
	void ShowDefaultCursor();

	UFUNCTION(BlueprintCallable)
	void ShowHandCursor();

	UFUNCTION(BlueprintCallable)
	void PlayButton(USimonButton* ButtonToPlay);

	UFUNCTION(BlueprintCallable)
	void StartTimerCount();

	UFUNCTION()
	void TurnOffButton(USimonButton* SimonButton);

	UFUNCTION()
	void CheckTimerValue();
	
	// Timer value for for beginning of the game
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float StartTimerValue = 10;

	// Value that will be added to the timer count at the next level of game difficult
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float PlusTimerValue = 5;

	UPROPERTY(BlueprintReadOnly)
	bool IsSomeButtonPlaying = false;

private:
	float TimerCount;

	FTimerHandle ButtonTimerHandle;
	FTimerHandle CountdownTimerHandle;

	void StartTimerCount(float SecondsCount);


};
