// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPCxGrabber.generated.h"

class USceneComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NPCXPRACTICALTEST_API UNPCxGrabber : public UActorComponent
{
	GENERATED_BODY()


	UPROPERTY(EditDefaultsOnly, Category = "Grab", meta = (AllowPrivateAcces = "true"))
	float ReachDistance = 100.f;

	class UInputComponent* InputComp = nullptr;
	class AActor* Owner = nullptr;
	USceneComponent* GrabComponent = nullptr;

	class INPCxPickUpInterface* GrabbedActor = nullptr;

public:	
	// Sets default values for this component's properties
	UNPCxGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupinputComponent();
	void SetupGrabLocation(USceneComponent* GrabComponent);

	void Grab();
	void Drop();
		
private:
	const FHitResult GetFirstPhysicsBodyInReach();
	const FVector GetReachLineStart();
	const FVector GetReachLineEnd();
};
