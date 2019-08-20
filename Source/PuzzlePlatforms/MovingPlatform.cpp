// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform() {
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() {
	Super::BeginPlay();

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}


void AMovingPlatform::Tick(float Deltatime) {
	Super::Tick(Deltatime);


	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	if (HasAuthority()) {
		//Converts local to global space for the B - A vector 
		FVector Location = GetActorLocation();
		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JourneyTraveled = (Location - GlobalStartLocation).Size();

		if (JourneyTraveled >= JourneyLength) {
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
		}
		FVector direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += speed * Deltatime * direction;
		SetActorLocation(Location);

	}

	
}
