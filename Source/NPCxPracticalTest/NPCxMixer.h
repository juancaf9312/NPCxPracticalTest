// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCxMixer.generated.h"

UENUM(BlueprintType)
enum class ERuleType : uint8
{
	SpecificClasses = 0,
	SameClasses,
	DifferentClasses
};

USTRUCT()
struct FRecipe 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray< TSubclassOf<AActor>> OutputActorClasses;

	UPROPERTY(EditDefaultsOnly)
	ERuleType Rule;

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "Rule == ERuleType::SpecificClasses"))
	TArray< TSubclassOf<AActor>> InputActorClasses;
};

UCLASS()
class NPCXPRACTICALTEST_API ANPCxMixer : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Mixer, meta = (AllowPrivateAccess = "true"))
	TArray<FRecipe> RecipeList;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Box = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Mixer, meta = (AllowPrivateAccess = "true"))
	TArray< TSubclassOf<AActor>> ValidClasses;
	
public:	
	// Sets default values for this actor's properties
	ANPCxMixer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void AddObjectToMixer(AActor* ActorToAdd);
	void RemoveObjectFromMixer(AActor* ActorToRemove);

	void Mix();
	void SpawnResultObject(TSubclassOf<AActor>& OutputActorClass);

private:
	TArray<AActor*> ActorsInside;

	bool CheckActorClass(AActor* ActorToCheck);
};
