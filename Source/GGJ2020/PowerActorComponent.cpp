// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerActorComponent.h"
#include "GameFramework/Actor.h"

UPowerActorComponent::UPowerActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bEditableWhenInherited = true;
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

bool UPowerActorComponent::TransferPowerTo(AActor* Target, float AmountToTransfer)
{
	check(Target != nullptr);
	UPowerActorComponent* TargetComponent = Target->FindComponentByClass<UPowerActorComponent>();
	return TransferPower(this, TargetComponent, AmountToTransfer);
}

bool UPowerActorComponent::TransferPowerFrom(AActor* Target, float AmountToTransfer)
{
	check(Target != nullptr);
	UPowerActorComponent* TargetComponent = Target->FindComponentByClass<UPowerActorComponent>();
	return TransferPower(TargetComponent, this, AmountToTransfer);
}

bool UPowerActorComponent::TransferPower(UPowerActorComponent* From, UPowerActorComponent* To, float AmountToTransfer)
{
	check(AmountToTransfer >= 0);
	if (From == nullptr || To == nullptr)
	{
		return false;
	}
	if (From->GetPowerAmount() < AmountToTransfer)
	{
		return false;
	}

	From->AddPowerAmount(-1.0f * AmountToTransfer);
	To->AddPowerAmount(AmountToTransfer);

	return true;
}

