// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCxMixer.generated.h"


UCLASS()
class NPCXPRACTICALTEST_API ANPCxMixer : public AActor
{
	GENERATED_BODY()


	UPROPERTY(VisibleDefaultsOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Box = nullptr;
	
public:	
	// Sets default values for this actor's properties
	ANPCxMixer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnComponentEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void AddObjectToMixer();
	void RemoveObjectFromMixer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
