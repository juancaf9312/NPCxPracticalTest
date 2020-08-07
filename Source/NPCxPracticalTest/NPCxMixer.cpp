// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCxMixer.h"
#include "Components/BoxComponent.h"
#include "NPCxPickUpInterface.h"

// Sets default values
ANPCxMixer::ANPCxMixer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("MixerArea");
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetHiddenInGame(false);
	Box->SetBoxExtent(FVector(64,64,128));
	SetRootComponent(Box);

}

// Called when the game starts or when spawned
void ANPCxMixer::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ANPCxMixer::OnComponentBeginOverlapEvent);
	Box->OnComponentEndOverlap.AddDynamic(this, &ANPCxMixer::OnComponentEndOverlapEvent);
	
}

void ANPCxMixer::OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ANPCxMixer::OnComponentEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ANPCxMixer::AddObjectToMixer()
{
}

void ANPCxMixer::RemoveObjectFromMixer()
{
}

// Called every frame
void ANPCxMixer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

