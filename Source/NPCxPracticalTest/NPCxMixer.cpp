// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCxMixer.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "NPCxPickUpInterface.h"


// Sets default values
ANPCxMixer::ANPCxMixer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>("MixerArea");
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
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

	TArray<AActor*> InitialOverlappingActors;
	Box->GetOverlappingActors(InitialOverlappingActors);
	for (AActor* OverlapingActor : InitialOverlappingActors) {
		if (!CheckActorClass(OverlapingActor)) {
			OverlapingActor->Destroy();
			continue;
		}
		AddObjectToMixer(OverlapingActor);
	}
}

void ANPCxMixer::OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!CheckActorClass(OtherActor)) {
		OtherActor->Destroy();
		return;
	}
	AddObjectToMixer(OtherActor);
}

void ANPCxMixer::OnComponentEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	RemoveObjectFromMixer(OtherActor);
}

void ANPCxMixer::AddObjectToMixer(AActor* ActorToAdd)
{
	ActorsInside.Push(ActorToAdd);
	if (ActorsInside.Num() >= 2) {
		Mix();
	}
}

void ANPCxMixer::RemoveObjectFromMixer(AActor* ActorToRemove)
{
	ActorsInside.Remove(ActorToRemove);
}

void ANPCxMixer::Mix()
{
	for (FRecipe Recipe : RecipeList)
	{
		bool bSuccess = true;

		switch (Recipe.Rule)
		{
		case ERuleType::SameClasses:
			{
				UClass* ActorClass = ActorsInside[0]->GetClass();
				for (AActor* Actor : ActorsInside) {
					if (ActorClass != Actor->GetClass()) bSuccess = false;
				}

				if (bSuccess) {
					SpawnResultObject(Recipe.OutputActorClasses[UKismetMathLibrary::RandomIntegerInRange(0, Recipe.OutputActorClasses.Num() - 1)]);
					return;
				}
			}
			break;
		case ERuleType::DifferentClasses:

			for (int i = 0; i < ActorsInside.Num() -1 ; i++) {
				for (int j = i + 1; j < ActorsInside.Num(); j++) {
					if (ActorsInside[i]->GetClass() == ActorsInside[j]->GetClass())bSuccess = false;
				}
			}
			
			if (bSuccess) {
				SpawnResultObject(Recipe.OutputActorClasses[UKismetMathLibrary::RandomIntegerInRange(0, Recipe.OutputActorClasses.Num() - 1)]);
				return;
			}
			break;
		case ERuleType::SpecificClasses:
			{
				TArray<AActor*> ActorList = ActorsInside;
				for (TSubclassOf<AActor> InputActorClass : Recipe.InputActorClasses) {
					AActor* SuccessActor = nullptr;
					for (AActor* ActorToCompare : ActorList) {
						if (ActorToCompare->IsA(InputActorClass)) {
							SuccessActor = ActorToCompare;
							break;
						}
					}
					if (!SuccessActor) bSuccess = false;

					ActorList.Remove(SuccessActor);
				}

				if (bSuccess) {
					SpawnResultObject(Recipe.OutputActorClasses[UKismetMathLibrary::RandomIntegerInRange(0, Recipe.OutputActorClasses.Num() - 1)]);
					return;
				}
			}
			break;
		}
	}
}

void ANPCxMixer::SpawnResultObject(TSubclassOf<AActor>& OutputActorClass)
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning"))
	TArray<AActor*> DeletingActors = ActorsInside;
	ActorsInside.Reset();

	for (AActor* ActorToMix : DeletingActors) {
		ActorToMix->SetActorEnableCollision(false);
		ActorToMix->SetLifeSpan(0.1f);
	}
	
	GetWorld()->SpawnActor<AActor>(OutputActorClass, FTransform(GetActorLocation()));
}

bool ANPCxMixer::CheckActorClass(AActor* ActorToCheck)
{
	for (TSubclassOf<AActor> SubClass : ValidClasses)
	{
		if (ActorToCheck->IsA(SubClass))
			return true;
	}

	for (FRecipe Recipe : RecipeList) {
		for (TSubclassOf<AActor> SubClass : Recipe.InputActorClasses) {
			if (ActorToCheck->IsA(SubClass))
				return true;
		}
	}
	return false;
}

