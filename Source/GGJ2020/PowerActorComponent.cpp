// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerActorComponent.h"

UPowerActorComponent::UPowerActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UPowerActorComponent::BeginPlay()
{
	Super::BeginPlay();
}

float UPowerActorComponent::GetPowerAmount()
{
	return PowerAmount;
}

void UPowerActorComponent::SetPowerAmount(float NewAmount)
{
	if (NewAmount >= 0)
	{
		PowerAmount = NewAmount;

		OnPowerChanged.Broadcast();
	}
}

void UPowerActorComponent::SetPowerLimit(float NewLimit)
{
	if (NewLimit >= 0)
	{
		PowerLimit = NewLimit;

		if (PowerAmount > PowerLimit)
		{
			PowerAmount = PowerLimit;
			OnPowerChanged.Broadcast();
		}
	}
}

bool UPowerActorComponent::AddPowerAmount(float AmountToAdd)
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

bool UPowerActorComponent::TransferPowerTo(UPowerActorComponent * DestinationComponent, float PowerToTransfer)
{
	return TransferPower(this, DestinationComponent, PowerToTransfer);
}

bool UPowerActorComponent::TransferPowerFrom(UPowerActorComponent * SourceComponent, float PowerToTransfer)
{
	return TransferPower(SourceComponent, this, PowerToTransfer);
}

bool UPowerActorComponent::TransferPower(UPowerActorComponent * SourceComponent, UPowerActorComponent * DestinationComponent, float PowerToTransfer)
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

