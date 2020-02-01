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
	// Sets default values for this component's properties
	UPowerActorComponent();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
		int PowerAmount{ 0 };

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category="Power component")
		FPowerChangedDelegate OnPowerChanged;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Power component")
		int GetPowerAmount();

	UFUNCTION(BlueprintCallable, Category = "Power component")
		void SetPowerAmount(int NewAmount);

	UFUNCTION(BlueprintCallable, Category = "Power component")
		bool AddPowerAmount(int AmountToAdd);

	UFUNCTION(BlueprintCallable, Category="Power component")
		bool TransferPowerTo(UPowerActorComponent* DestinationComponent, int PowerToTransfer);
	
	UFUNCTION(BlueprintCallable, Category = "Power component")
		bool TransferPowerFrom(UPowerActorComponent* SourceComponent, int PowerToTransfer);
			
	UFUNCTION(BlueprintCallable, Category = "Power component")
		bool TransferPower(UPowerActorComponent* SourceComponent, UPowerActorComponent* DestinationComponent, int PowerToTransfer);
};
