// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ButtonStaticMesh.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class SIMONSAYS_API UButtonStaticMesh : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void Push();

	UFUNCTION(BlueprintCallable)
	void UnPush();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float PushOffset = 1.f;
private:
	FVector StartLocation;
	bool IsPushed = false;
};
