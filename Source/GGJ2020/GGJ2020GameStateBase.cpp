// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ2020GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"


void AGGJ2020GameStateBase::BeginPlay()
{
	Super::BeginPlay();

}

void AGGJ2020GameStateBase::AddPanel(APanel * NewPanel)
{
	if (NewPanel != nullptr)
	{
		if (NewPanel->bIsPuzzleSolved)
		{
			SolvedPanels.Add(NewPanel);
		}
		else
		{
			UnsolvedPanels.Add(NewPanel);
		}
	}
}

bool AGGJ2020GameStateBase::MovePanelToSolved(APanel * PanelToMove)
{
	if (PanelToMove != nullptr)
	{
		if (UnsolvedPanels.RemoveSingle(PanelToMove) > 0)
		{
			SolvedPanels.Add(PanelToMove);

			return true;
		}
	}

	return false;
}

TArray<APanel*> AGGJ2020GameStateBase::GetSolvedPanels()
{
	return SolvedPanels;
}

bool AGGJ2020GameStateBase::GetGameInProgress()
{
	return bIsGameInProgress;
}

void AGGJ2020GameStateBase::SetGameInProgress(bool bNewGameInProgress)
{
	bIsGameInProgress = bNewGameInProgress;
}
