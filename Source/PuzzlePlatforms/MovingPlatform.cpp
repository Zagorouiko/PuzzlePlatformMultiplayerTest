// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform() {
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeingPlay() {
	Super::BeginPlay();

	//if (HasAuthority()) {
	//	SetReplicates(true);
	//	SetReplicateMovement(true);
	//}
}


void AMovingPlatform::Tick(float Deltatime) {
	Super::Tick(Deltatime);


	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	FVector Location = GetActorLocation();

	if (HasAuthority()) {
		//Converts local to global space for the B - A vector 
		FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
		FVector direction = (GlobalTargetLocation - Location).GetSafeNormal();
		Location += direction * (speed * Deltatime);
		SetActorLocation(Location);
	}

	
}
