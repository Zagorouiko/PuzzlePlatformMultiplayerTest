// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform() {
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float Deltatime) {
	Super::Tick(Deltatime);

	FVector Location = GetActorLocation();

	if (HasAuthority()) {
		Location += FVector(speed * Deltatime, 0, 0);
		SetActorLocation(Location);
	}

	
}
