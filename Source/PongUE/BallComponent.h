// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Players.h"

#include "BallComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PONGUE_API UBallComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBallComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//component allowing the player to be seen 
	UPROPERTY(editanywhere)
		UPrimitiveComponent* VisibleComponent;

	UPROPERTY(editanywhere)
		float throwForce;

	UPROPERTY(editanywhere)
		float minimalAngle;

	UPROPERTY(editanywhere)
		float minimalVelocity;

	void ThrowObject(float power);

	void SetRandomOrientation();

	void ResetBall();

	void StopBall();

	//detect when collision happen and react
	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//UI
	UPROPERTY(editanywhere)
		TSubclassOf<UUserWidget> bp_ui;

	UPROPERTY(editanywhere)
		class UUserWidget* created_ui;

	UPROPERTY(editanywhere)
		class UTextBlock* Player1_Score;

	UPROPERTY(editanywhere)
		class UTextBlock* Player2_Score;

	UPROPERTY(editanywhere)
		TSubclassOf<UUserWidget> bp_endgame;

	UPROPERTY(editanywhere)
		class UUserWidget* created_endgame;

	UPROPERTY(editanywhere)
		class UTextBlock* Winner_Text;

	//Scores
	UPROPERTY(editanywhere)
		int scoreP1;

	UPROPERTY(editanywhere)
		int scoreP2;

	//Players
	UPROPERTY(editanywhere)
		TArray<APlayers*> players;
};
