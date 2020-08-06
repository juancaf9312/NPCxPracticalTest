// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCxPracticalTestCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class ANPCxPracticalTestCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Mesh1P = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UNPCxGrabber* GrabberComp = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* GrabLocation;

public:
	ANPCxPracticalTestCharacter();

protected:
	virtual void BeginPlay();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate = 45.f;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate = 45.f;

protected:

	void MoveForward(float Val);
	void MoveRight(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	
protected:

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:

	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

