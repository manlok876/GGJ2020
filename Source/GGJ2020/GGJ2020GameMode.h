// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Panel.h"
#include "GGJ2020GameStateBase.h"
#include "GGJ2020GameMode.generated.h"

UCLASS(minimalapi)
class AGGJ2020GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGGJ2020GameMode();

	virtual void BeginPlay() override;

protected:

	APlayerController* GetPlayerController();

	UFUNCTION()
		void PanelSolveHandler(APanel* SolvedPanel);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player HUD")
		TSubclassOf<UUserWidget> wPlayerHUD;

	UPROPERTY(BlueprintReadWrite, Category = "Player HUD")
		UUserWidget* PlayerHUDWidget;


};



