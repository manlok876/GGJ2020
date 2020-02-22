// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"
#include "Engine/Engine.h"
#include "GGJ2020Character.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (Button != nullptr)
	{
		Button->SetElevator(this);
	}

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(GetRootComponent());
	CollisionComponent->SetRelativeTransform(CollisionBoxTransform);
	CollisionComponent->SetGenerateOverlapEvents(true);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AElevator::PlayerOverlapHandler);
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	
	/*FScriptDelegate ElevatorOverlapDelegate;
	ElevatorOverlapDelegate.BindUFunction(this, "ElevatorOverlapHandler");
	CollisionComponent->OnComponentBeginOverlap.Add(ElevatorOverlapDelegate);*/
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AElevator::ElevatorOverlapHandler(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->StaticClass == AGGJ2020Character::StaticClass)
		{
			CallOnPlayerEnteredElevator();
			CloseDoors();
		}
	}
}

void AElevator::PlayerOverlapHandler(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString("Overlapping box"));
	}*/

 	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (Cast<AGGJ2020Character>(OtherActor) != nullptr)
		{
			CallOnPlayerEnteredElevator();
			CloseDoors();
		}
	}
}

void AElevator::CallOnPlayerEnteredElevator()
{
	OnPlayerEnteredElevator.Broadcast();
}

AElevatorButton * AElevator::GetElevatorButton()
{
	return Button;
}

void AElevator::SetElevatorButton(AElevatorButton * NewButton)
{
	Button = NewButton;

	if (Button != nullptr)
	{
		Button->SetElevator(this);
	}
}

void AElevator::CloseDoors_Implementation()
{
}

void AElevator::OpenDoors_Implementation()
{
}

