// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GGJ2020GameMode.h"
#include "GGJ2020HUD.h"
#include "GGJ2020Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

AGGJ2020GameMode::AGGJ2020GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGGJ2020HUD::StaticClass();
}

void AGGJ2020GameMode::BeginPlay()
{
	Super::BeginPlay();

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
}

void AGGJ2020GameMode::PanelSolveHandler(APanel * SolvedPanel)
{
	GetGameState<AGGJ2020GameStateBase>()->MovePanelToSolved(SolvedPanel);
}
