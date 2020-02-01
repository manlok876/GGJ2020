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
	float OldPower = PowerAmount;

	PowerAmount = FMath::Clamp(NewAmount, 0.0f, PowerLimit);

	if (OldPower != PowerAmount)
	{
		OnPowerChanged.Broadcast();
	}
}

void UPowerActorComponent::SetPowerLimit(float NewLimit)
{
	NewLimit = FMath::Max(0.0f, NewLimit);
	PowerLimit = NewLimit;
	if (PowerAmount > PowerLimit)
	{
		SetPowerAmount(NewLimit);
	}
}

float UPowerActorComponent::AddPowerAmount(float AmountToAdd, bool FailIfOutOfBounds)
{
	float TargetAmount = PowerAmount + AmountToAdd;

	if ((TargetAmount < 0.0f || TargetAmount > PowerLimit) && FailIfOutOfBounds)
	{
		return 0.0f;
	}

	float OldPower = PowerAmount;
	SetPowerAmount(TargetAmount);
	return PowerAmount - OldPower;
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
	check(PowerToTransfer >= 0);
	if (SourceComponent->GetPowerAmount() < PowerAmount)
	{
		return false;
	}

	SourceComponent->AddPowerAmount(-1.0f * PowerToTransfer);
	DestinationComponent->AddPowerAmount(PowerToTransfer);

	return false;
}

