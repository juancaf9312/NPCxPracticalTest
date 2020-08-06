// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCxGrabber.h"

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
	//if (!Owner) return;
	//if (InputComp) {
	//	InputComp->BindAction("Grab", IE_Pressed, this, &UNPCxGrabber::Grab);
	//	InputComp->BindAction("Grab", IE_Released, this, &UNPCxGrabber::Drop);
	//}
	//else {
	//	UE_LOG(LogTemp, Error, TEXT("ERROR:Input component of %s cannot be found"), *Owner->GetName())
	//}
}

void UNPCxGrabber::Grab()
{
}

void UNPCxGrabber::Drop()
{
}
