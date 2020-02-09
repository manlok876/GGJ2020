// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2020_API AMainMenuGameMode : public AGameMode
{
	GENERATED_BODY()

		AMainMenuGameMode();

	virtual void BeginPlay() override;

protected:

	UFUNCTION()
	APlayerController* GetPlayerController();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main menu")
		TSubclassOf<UUserWidget> wMainMenu;

	UUserWidget* MainMenuWidget;

	
};
