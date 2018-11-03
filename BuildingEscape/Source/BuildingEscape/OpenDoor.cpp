// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s missing trigger volume"), *Owner->GetName())
	}
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// Poll the trigger volume


	if (GetTotalMassOfActorsOnPlate() > TriggerMass) 
	{
		OnOpen.Broadcast();
	}
	//check if its time to close the door
	else
	{
		OnClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{

	float TotalMass = 0.0f;

	//find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass;  }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//iterate through them adding their masses

	for (const auto& GetOverlappingActors : OverlappingActors)
	{
		TotalMass += GetOverlappingActors->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s in pressure plate"), *GetOverlappingActors->GetName())
	}


	return TotalMass;
}