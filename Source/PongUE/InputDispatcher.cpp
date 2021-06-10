// Fill out your copyright notice in the Description page of Project Settings.


#include "InputDispatcher.h"

// Sets default values
AInputDispatcher::AInputDispatcher()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//receive input from player 0
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

// Called when the game starts or when spawned
void AInputDispatcher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInputDispatcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInputDispatcher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(InputComponent);

	for (int i = 0; i < players.Num(); i++)
	{
		InputComponent->BindAxis(MovementsAxisName[i], players[i], &APlayers::MoveForward);
	}
}

