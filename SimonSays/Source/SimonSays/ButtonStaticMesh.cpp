// Fill out your copyright notice in the Description page of Project Settings.

#include "ButtonStaticMesh.h"

void UButtonStaticMesh::Push() {
	if (!IsPushed) {
		IsPushed = true;
		StartLocation = GetComponentLocation();
		FVector NewLocation = StartLocation - FVector(0, 0, PushOffset);
		SetRelativeLocation(NewLocation);
	}
}

void UButtonStaticMesh::UnPush() {
	if (IsPushed) {
		IsPushed = false;
		SetWorldLocation(StartLocation);
	}
}
