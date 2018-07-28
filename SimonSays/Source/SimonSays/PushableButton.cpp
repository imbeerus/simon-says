// Fill out your copyright notice in the Description page of Project Settings.

#include "PushableButton.h"

void UPushableButton::Push() {
	if (!IsPushed) {
		IsPushed = true;
		StartLocation = GetComponentLocation();
		StartLocation.Z -= PushOffset;
		SetWorldLocation(StartLocation);
	}
}

void UPushableButton::UnPush() {
	if (IsPushed) {
		IsPushed = false;
		StartLocation.Z += PushOffset;
		SetWorldLocation(StartLocation);
	}
}