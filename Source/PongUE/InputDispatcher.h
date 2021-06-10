// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Players.h"
#include "InputDispatcher.generated.h"

UCLASS()
class PONGUE_API AInputDispatcher : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AInputDispatcher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(editanywhere)
		TArray<FName> MovementsAxisName;

	UPROPERTY(editanywhere)
		TArray<APlayers*> players;
};
