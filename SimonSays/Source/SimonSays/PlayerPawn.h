// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class USimonButton;

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

	UFUNCTION()
	void TurnOffButton(USimonButton* SimonButton);
	
	UPROPERTY(BlueprintReadOnly)
	bool IsSomeButtonPlaying = false;

private:
	FTimerHandle TimerHandle;

};
