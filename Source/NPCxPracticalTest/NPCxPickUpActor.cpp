// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCxPickUpActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ANPCxPickUpActor::ANPCxPickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetGenerateOverlapEvents(true);
	SetRootComponent(StaticMesh);

}

// Called when the game starts or when spawned
void ANPCxPickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCxPickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPCxPickUpActor::PickUp(USceneComponent* AttachTo)
{
	if (StaticMesh) {
		StaticMesh->SetSimulatePhysics(false);


		AttachToComponent(AttachTo, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void ANPCxPickUpActor::Drop()
{
	if (StaticMesh) {
		StaticMesh->SetSimulatePhysics(true);

		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}
}

