// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGJ2020_API UPowerActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPowerActorComponent();

	//DECLARE_DELEGATE_OneParam(FChangePowerDelegate)

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
		int PowerAmount{ 0 };

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Power component")
		int GetPowerAmount();

	UFUNCTION(BlueprintCallable, Category = "Power component")
		void SetPowerAmount(int NewAmount);

	UFUNCTION(BlueprintCallable, Category = "Power component")
		bool AddPowerAmount(int AmountToAdd);

		
};
