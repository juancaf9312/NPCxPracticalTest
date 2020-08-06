// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCxGrabber.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"

#include "NPCxPickUpInterface.h"

// Sets default values for this component's properties
UNPCxGrabber::UNPCxGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNPCxGrabber::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	SetupinputComponent();
	// ...
	
}


// Called every frame
void UNPCxGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UNPCxGrabber::SetupinputComponent()
{
	if (!Owner) return;

	InputComp = Owner->FindComponentByClass<UInputComponent>();
	if (InputComp) {
		InputComp->BindAction("Grab", IE_Pressed, this, &UNPCxGrabber::Grab);
		InputComp->BindAction("Grab", IE_Released, this, &UNPCxGrabber::Drop);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("ERROR:Input component of %s cannot be found"), *Owner->GetName())
	}
}

void UNPCxGrabber::SetupGrabLocation(USceneComponent* GrabLocation)
{
	GrabComponent = GrabLocation;
}

void UNPCxGrabber::Grab()
{
	const FHitResult Hit = GetFirstPhysicsBodyInReach();

	GrabbedActor = Cast<INPCxPickUpInterface>(Hit.GetActor());

	if (GrabbedActor && GrabComponent) {
		GrabbedActor->PickUp(GrabComponent);
	}
}

void UNPCxGrabber::Drop()
{
	if (GrabbedActor) {
		GrabbedActor->Drop();
	}
}

const FHitResult UNPCxGrabber::GetFirstPhysicsBodyInReach()
{
	/// Ray-cast (AKA ray cast) out to reach distance
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return HitResult;
}

const FVector UNPCxGrabber::GetReachLineStart()
{
	/// Get the player viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return PlayerViewPointLocation;
}


const FVector UNPCxGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return  PlayerViewPointLocation + PlayerViewPointRotation.Vector() * ReachDistance;
}