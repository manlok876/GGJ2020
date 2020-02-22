// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Panel.h"
#include "GGJ2020GameStateBase.h"
#include "PowerActorComponent.h"
#include "PlayerHUD.h"
#include "Elevator.h"
#include "GGJ2020GameMode.generated.h"

UCLASS(minimalapi)
class AGGJ2020GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGGJ2020GameMode();

	virtual void BeginPlay() override;

protected:

	UFUNCTION()
	APlayerController* GetPlayerController();

	UFUNCTION()
		void PlayerPowerChangedHandler();

	UFUNCTION()
		void PanelSolveHandler(APanel* SolvedPanel);

	UFUNCTION()
		void PlayerEnteredElevatorHandler();

	UFUNCTION()
		void ProceedGameOver();
	
	UFUNCTION()
		void ProceedWin();

	UPROPERTY()
		APlayerController* PlayerController;

	UPROPERTY()
		UPowerActorComponent* PlayerPower;


	//Widgets
	//HUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player HUD")
		TSubclassOf<UPlayerHUD> wPlayerHUD;

	UPROPERTY(BlueprintReadOnly, Category = "Player HUD")
		UUserWidget* PlayerHUDWidget;

	//Game over
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game over")
		TSubclassOf<UUserWidget> wGameOver;

	UPROPERTY(BlueprintReadOnly, Category = "Game over")
		UUserWidget* GameOverWidget;
	
	//Win
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game win")
		TSubclassOf<UUserWidget> wGameWin;

	UPROPERTY(BlueprintReadOnly, Category = "Game win")
		UUserWidget* GameWinWidget;

	//Pause
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game pause")
		TSubclassOf<UUserWidget> wGamePause;

	UPROPERTY(BlueprintReadOnly, Category = "Game pause")
		UUserWidget* GamePauseWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game win")
		TSubclassOf<AElevator> ElevatorClass;

	UPROPERTY(BlueprintReadOnly, Category = "Game win")
		AElevator* Elevator;


public:


};



