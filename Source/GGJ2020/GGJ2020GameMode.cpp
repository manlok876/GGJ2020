// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GGJ2020GameMode.h"
#include "GGJ2020HUD.h"
#include "GameFramework/Character.h"
#include "GGJ2020Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "UObject/ConstructorHelpers.h"

AGGJ2020GameMode::AGGJ2020GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	//HUDClass = AGGJ2020HUD::StaticClass();
}

void AGGJ2020GameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetPlayerController();

	//Show player HUD
	if (wPlayerHUD)
	{
		if (PlayerController != nullptr)
		{
			PlayerHUDWidget = CreateWidget<UUserWidget>(PlayerController, wPlayerHUD);

			if (PlayerHUDWidget != nullptr)
			{
				PlayerHUDWidget->AddToViewport();

				FInputModeGameOnly InputModeGame;
				PlayerController->SetInputMode(InputModeGame);
				//PlayerController->bShowMouseCursor = true;
			}
		}
	}

	//Find all panels and add them to specific arrays
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APanel::StaticClass(), Actors);

	FScriptDelegate PanelSolvedDelegate;
	PanelSolvedDelegate.BindUFunction(this, "PanelSolveHandler");

	if (Actors.Num() > 0)
	{
		for (auto& Actor : Actors)
		{
			APanel* Panel = Cast<APanel>(Actor);
			if (Panel != nullptr)
			{
				GetGameState<AGGJ2020GameStateBase>()->AddPanel(Panel);

				Panel->OnPuzzleSolved.Add(PanelSolvedDelegate);
			}
		}
	}


	//Update panels icons on HUD
	if (PlayerHUDWidget != nullptr)
	{
		Cast<UPlayerHUD>(PlayerHUDWidget)->OnUpdateSolvedPanels(GetGameState<AGGJ2020GameStateBase>()->GetSolvedPanelsNum(), GetGameState<AGGJ2020GameStateBase>()->GetUnsolvedPanelsNum());
	}


	//Tracking the player's power
	PlayerPower = Cast<AGGJ2020Character>(GetPlayerController()->GetCharacter())->GetPowerComponent();
	
	if(PlayerPower != nullptr)
	{
		FScriptDelegate PlayerPowerChangedDelegate;
		PlayerPowerChangedDelegate.BindUFunction(this, "PlayerPowerChangedHandler");
		PlayerPower->OnPowerChanged.Add(PlayerPowerChangedDelegate);
	}
}

APlayerController * AGGJ2020GameMode::GetPlayerController()
{
	APlayerController* PlayerController{ nullptr };
	if (GameState->PlayerArray.IsValidIndex(0))
	{
		APlayerState* PlayerState = GameState->PlayerArray[0];
		if (PlayerState != nullptr)
		{
			APawn* PlayerPawn = PlayerState->GetPawn();

			if (PlayerPawn != nullptr)
			{
				PlayerController = Cast<APlayerController>(PlayerPawn->GetController());
			}
		}
	}

	return PlayerController;
}

void AGGJ2020GameMode::PlayerPowerChangedHandler()
{
	if (PlayerPower != nullptr)
	{
		//Loose condition
		if (PlayerPower->GetPowerAmount() <= 0)
		{
			ProceedGameOver();
		}
	}
}

void AGGJ2020GameMode::PanelSolveHandler(APanel * SolvedPanel)
{
	GetGameState<AGGJ2020GameStateBase>()->MovePanelToSolved(SolvedPanel);

	if (PlayerHUDWidget != nullptr)
	{
		Cast<UPlayerHUD>(PlayerHUDWidget)->OnUpdateSolvedPanels(GetGameState<AGGJ2020GameStateBase>()->GetSolvedPanelsNum(), GetGameState<AGGJ2020GameStateBase>()->GetUnsolvedPanelsNum());
	}
}

void AGGJ2020GameMode::ProceedGameOver()
{
	GetGameState<AGGJ2020GameStateBase>()->SetGameInProgress(false);

	//Remove Player HUD
	if (PlayerHUDWidget != nullptr)
	{
		PlayerHUDWidget->RemoveFromParent();
	}

	//Show Game over HUD
	if (wGameOver)
	{
		if (PlayerController != nullptr)
		{
			GameOverWidget = CreateWidget<UUserWidget>(PlayerController, wGameOver);

			if (GameOverWidget != nullptr)
			{
				GameOverWidget->AddToViewport();
				
				FInputModeUIOnly InputModeUI;
				PlayerController->SetInputMode(InputModeUI);
				PlayerController->bShowMouseCursor = true;
				PlayerController->StopMovement();
			}
		}
	}
}
