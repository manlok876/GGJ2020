// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElevatorButton.generated.h"


class AElevator;

UCLASS()
class GGJ2020_API AElevatorButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevatorButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "Game win")
		bool bIsActive{ false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game win")
		AElevator* Elevator;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Game win")
		void SetIsActive(bool bNewIsActive);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game win")
		bool GetIsActive();

	UFUNCTION()
		void SetElevator(AElevator* NewElevator);

};
