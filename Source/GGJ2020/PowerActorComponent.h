// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerActorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPowerChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGJ2020_API UPowerActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPowerActorComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
		float PowerAmount{ 0 };

public:
	UPROPERTY(BlueprintAssignable, Category="Power component")
		FPowerChangedDelegate OnPowerChanged;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Power component")
		float GetPowerAmount();

	UFUNCTION(BlueprintCallable, Category = "Power component")
		void SetPowerAmount(float NewAmount);

	UFUNCTION(BlueprintCallable, Category = "Power component")
		bool AddPowerAmount(float AmountToAdd);

	UFUNCTION(BlueprintCallable, Category="Power component")
		bool TransferPowerTo(UPowerActorComponent* DestinationComponent, float PowerToTransfer);
	
	UFUNCTION(BlueprintCallable, Category = "Power component")
		bool TransferPowerFrom(UPowerActorComponent* SourceComponent, float PowerToTransfer);
			
	UFUNCTION(BlueprintCallable, Category = "Power component")
		bool TransferPower(UPowerActorComponent* SourceComponent, UPowerActorComponent* DestinationComponent, float PowerToTransfer);
};
