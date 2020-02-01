// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerActorComponent.h"

// Sets default values for this component's properties
UPowerActorComponent::UPowerActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPowerActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPowerActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UPowerActorComponent::GetPowerAmount()
{
	return PowerAmount;
}

void UPowerActorComponent::SetPowerAmount(int NewAmount)
{
	if (NewAmount >= 0)
	{
		PowerAmount = NewAmount;

		OnPowerChanged.Broadcast();
	}
}

bool UPowerActorComponent::AddPowerAmount(int AmountToAdd)
{
	//PowerAmount = FMath::Max(PowerAmount + AmountToAdd, 0);
	if (PowerAmount + AmountToAdd < 0)
	{
		PowerAmount = 0;

		OnPowerChanged.Broadcast();

		return false;
	}

	PowerAmount += AmountToAdd;
	OnPowerChanged.Broadcast();

	return true;
}

bool UPowerActorComponent::TransferPowerTo(UPowerActorComponent * DestinationComponent, int PowerToTransfer)
{
	return TransferPower(this, DestinationComponent, PowerToTransfer);
}

bool UPowerActorComponent::TransferPowerFrom(UPowerActorComponent * SourceComponent, int PowerToTransfer)
{
	return TransferPower(SourceComponent, this, PowerToTransfer);
}

bool UPowerActorComponent::TransferPower(UPowerActorComponent * SourceComponent, UPowerActorComponent * DestinationComponent, int PowerToTransfer)
{
	if (SourceComponent->GetPowerAmount() < PowerAmount)
	{
		return false;
	}

	SourceComponent->AddPowerAmount(-1 * PowerToTransfer);
	DestinationComponent->AddPowerAmount(PowerToTransfer);

	OnPowerChanged.Broadcast();

	return false;
}

