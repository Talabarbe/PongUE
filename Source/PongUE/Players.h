// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Logging/LogVerbosity.h"
#include "Players.generated.h"

UCLASS()
class PONGUE_API APlayers : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayers();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector movement;

	UPROPERTY(editanywhere)
		UStaticMeshComponent* VisibleComponent;

	UPROPERTY(editanywhere)
		float speed;

	UPROPERTY(editanywhere)
		AActor* upLimit;

	UPROPERTY(editanywhere)
		AActor* downLimit;

	UPROPERTY(editanywhere)
		bool gameOver;

	void MoveForward(float value);

	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
