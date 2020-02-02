// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "PanelButtonComponent.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNodeClicked, int, NodeNum);

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GGJ2020_API UPanelButtonComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UPanelButtonComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int NodeNumber;

	UPROPERTY(BlueprintAssignable)
	FOnNodeClicked OnCLickDelegate;

	UFUNCTION()
	void ClickReaction(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
};
