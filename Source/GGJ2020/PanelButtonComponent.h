// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "PanelButtonComponent.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2020_API UPanelButtonComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UPanelButtonComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int NodeNumber;
};
