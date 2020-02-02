// Fill out your copyright notice in the Description page of Project Settings.


#include "PanelButtonComponent.h"
#include "UObject/ConstructorHelpers.h"

UPanelButtonComponent::UPanelButtonComponent()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ButtonMeshFinder(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (ButtonMeshFinder.Succeeded())
	{
		SetStaticMesh(ButtonMeshFinder.Object);
	}
	OnClicked.AddDynamic(this, &UPanelButtonComponent::ClickReaction);
}

void UPanelButtonComponent::ClickReaction(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	OnCLickDelegate.Broadcast(NodeNumber);
}
