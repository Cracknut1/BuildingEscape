// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindHandlePhysicsComponent();
	SetupInputComponent();


}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key pressed"))

	/// line trace and see if we reach any actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();
		///if we hit something, attach physics handle
		//TODO attach physics channel
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key released"))
		//TODO release physics
}

void UGrabber::FindHandlePhysicsComponent()
{
	/// Look for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		//Physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesnt have physics handle"), *GetOwner()->GetName());
	}

}

void UGrabber::SetupInputComponent()
{
	///loook for input component at runtime
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s component found"), *GetOwner()->GetName());

		///bind input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s component not found"), *GetOwner()->GetName())
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;


	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// ray-cast out to reach distance 
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType
	(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	// see what we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("trace hit :%s"), (*ActorHit->GetName()))
	};

	return FHitResult();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if physics handle is attached, move the object we're holding

	// Get player viewpoint this tick
	
}


