// Fill out your copyright notice in the Description page of Project Settings.

#define LOG(fstring) GLog->Log(fstring)
#include "Players.h"

// Sets default values
APlayers::APlayers()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//variables initialisations
	speed = 1500.0f;

	//create a empty root 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//create a mesh component
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MYMESH"));
	//attach mesh to root compoenent
	VisibleComponent->SetupAttachment(RootComponent);

	//looking for a static mesh to have a visual on our compoenent
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MyVisualAsset(TEXT("/Game/02_Meshs/Cube"));
	//
	if (MyVisualAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(MyVisualAsset.Object);
	}
	else
	{
		GLog->Log("LOADING FAIL");
	}

	//activate physic
	VisibleComponent->SetSimulatePhysics(false);
	VisibleComponent->SetNotifyRigidBodyCollision(true);

	//set collision profile to block all
	VisibleComponent->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	//play OnCompHit function when colliding another object
	VisibleComponent->OnComponentHit.AddDynamic(this, &APlayers::OnCompHit);
}

// Called when the game starts or when spawned
void APlayers::BeginPlay()
{
	Super::BeginPlay();
	
	GLog->Log("STARTING PLAYER 1");
}

// Called every frame
void APlayers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!movement.IsZero() && !gameOver)
	{
		FVector newLocation = VisibleComponent->GetComponentLocation() + ((VisibleComponent->GetForwardVector() * movement.X) * speed * DeltaTime);
		newLocation.X = FMath::Clamp(newLocation.X, downLimit->GetActorLocation().X + 150, upLimit->GetActorLocation().X - 150);
		VisibleComponent->SetWorldLocation(newLocation);
	}
}

// Called to bind functionality to input
void APlayers::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayers::MoveForward(float value)
{
	movement.X = FMath::Clamp(value, -1.0f, 1.0f);
}

void APlayers::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		//LOG(OtherActor->GetName());
	}
}

