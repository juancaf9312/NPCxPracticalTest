// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCxPickUpInterface.h"
#include "NPCxPickUpActor.generated.h"

UCLASS()
class NPCXPRACTICALTEST_API ANPCxPickUpActor : public AActor, public INPCxPickUpInterface
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAcces = "true"))
	class UStaticMeshComponent* StaticMesh = nullptr;
	
public:	
	// Sets default values for this actor's properties
	ANPCxPickUpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PickUp(USceneComponent* AttachTo);

	virtual void Drop();
};
