// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorButton.h"
#include "Elevator.h"

// Sets default values
AElevatorButton::AElevatorButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElevatorButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElevatorButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AElevatorButton::GetIsActive()
{
	return bIsActive;
}

void AElevatorButton::SetElevator(AElevator * NewElevator)
{
	Elevator = NewElevator;
}

void AElevatorButton::SetIsActive_Implementation(bool bNewIsActive)
{
	bIsActive = bNewIsActive;
}

