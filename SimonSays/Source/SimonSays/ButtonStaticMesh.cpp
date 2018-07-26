// Fill out your copyright notice in the Description page of Project Settings.

#include "ButtonStaticMesh.h"

void UButtonStaticMesh::Push() {
	if (!IsPushed) {
		IsPushed = true;
		StartLocation = GetComponentLocation();
		StartLocation.Z -= PushOffset;
		SetWorldLocation(StartLocation);
	}
}

void UButtonStaticMesh::UnPush() {
	if (IsPushed) {
		IsPushed = false;
		StartLocation.Z += PushOffset;
		SetWorldLocation(StartLocation);
	}
}
