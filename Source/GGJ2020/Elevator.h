// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ElevatorButton.h"
#include "Elevator.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerEnteredElevator);


UCLASS()
class GGJ2020_API AElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Game win")
		AElevatorButton* Button;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game win")
		UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game win")
		FTransform CollisionBoxTransform;
	
	UPROPERTY(EditAnywhere, Category = "Game win")
		USceneComponent* Root;

	UPROPERTY()
		FOnPlayerEnteredElevator OnPlayerEnteredElevator;

	UFUNCTION(BlueprintCallable, Category = "Game win")
		void ElevatorOverlapHandler(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Game win")
		void PlayerOverlapHandler(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Game win")
		void CallOnPlayerEnteredElevator();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game win")
		AElevatorButton* GetElevatorButton();

	UFUNCTION(BlueprintCallable, Category = "Game win")
		void SetElevatorButton(AElevatorButton* NewButton);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Game win")
		void OpenDoors();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Game win")
		void CloseDoors();
};
