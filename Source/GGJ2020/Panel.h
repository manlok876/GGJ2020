// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Panel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPuzzleSolved, APanel*, SolvedPanel);

UCLASS()
class GGJ2020_API APanel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APanel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category="Pannels|State")
		void CallOnPuzzleSolved();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category="Panels|State")
		FPuzzleSolved OnPuzzleSolved;

	UPROPERTY(EditAnywhere, Category = "Panels|State")
		bool bIsPuzzleSolved{ false };

};
