// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Panel.h"
#include "GGJ2020GameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2020_API AGGJ2020GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

private:
	UFUNCTION()
		virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Panels")
		TArray<APanel*> UnsolvedPanels;

	UPROPERTY(EditAnywhere, Category="Panels")
		TArray<APanel*> SolvedPanels;

	
	UPROPERTY(EditAnywhere, Category="Game state")
		bool bIsGameInProgress;

public:

	UFUNCTION(BlueprintCallable, Category = "Panels")
		void AddPanel(APanel* NewPanel);

	UFUNCTION(BlueprintCallable, Category = "Panels")
		bool MovePanelToSolved(APanel* PanelToMove);

	/*UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Panels")
		TArray<APanel*> GetSolvedPanels();*/

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Panels")
		int GetSolvedPanelsNum();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Panels")
		int GetUnsolvedPanelsNum();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game state")
		bool GetGameInProgress();

	UFUNCTION(BlueprintCallable, Category = "Game state")
		void SetGameInProgress(bool bNewGameInProgress);

};
