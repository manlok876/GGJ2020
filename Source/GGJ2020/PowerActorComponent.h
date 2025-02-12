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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float PowerAmount{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float PowerLimit{ 5 };

public:
	UPROPERTY(BlueprintAssignable, Category="Power component")
		FPowerChangedDelegate OnPowerChanged;

	UFUNCTION(BlueprintPure, Category = "Power component")
		float GetPowerAmount();

	UFUNCTION(BlueprintCallable, Category = "Power component")
		void SetPowerAmount(float NewAmount);

	UFUNCTION(BlueprintCallable, Category = "Power component")
		void SetPowerLimit(float NewLimit);

	UFUNCTION(BlueprintCallable, Category = "Power component")
		float AddPowerAmount(float AmountToAdd, bool FailIfOutOfBounds = false);

	UFUNCTION(BlueprintCallable, Category="Power component")
		bool TransferPowerTo(AActor* Target, float AmountToTransfer);
	
	UFUNCTION(BlueprintCallable, Category = "Power component")
		bool TransferPowerFrom(AActor* Target, float AmountToTransfer);
			
	UFUNCTION(BlueprintCallable, Category = "Power component")
		bool TransferPower(UPowerActorComponent* From, UPowerActorComponent* To, float AmountToTransfer);
};
