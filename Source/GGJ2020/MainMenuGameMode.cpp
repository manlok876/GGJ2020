// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "MainMenuHUD.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	//HUDClass = AMainMenuHUD::StaticClass();
}

void AMainMenuGameMode::BeginPlay()
{
	if (wMainMenu)
	{
		APlayerController* PlayerController = GetPlayerController();
		if (PlayerController != nullptr)
		{
			MainMenuWidget = CreateWidget<UUserWidget>(PlayerController, wMainMenu);

			if (MainMenuWidget != nullptr)
			{
				MainMenuWidget->AddToViewport();

				FInputModeUIOnly InputModeUI;
				PlayerController->SetInputMode(InputModeUI);
				PlayerController->bShowMouseCursor = true;
			}
		}
	}
}

APlayerController * AMainMenuGameMode::GetPlayerController()
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
