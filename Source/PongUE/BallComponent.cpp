// Fill out your copyright notice in the Description page of Project Settings.


#include "BallComponent.h"
#define LOG(fstring) GLog->Log(fstring)

// Sets default values for this component's properties
UBallComponent::UBallComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBallComponent::BeginPlay()
{
	Super::BeginPlay();

	VisibleComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	if (VisibleComponent)
	{
		//activate physic
		VisibleComponent->SetSimulatePhysics(true);
		//detect collisions
		VisibleComponent->SetNotifyRigidBodyCollision(true);
		//set collision profile
		VisibleComponent->BodyInstance.SetCollisionProfileName("BlockAllDynamic");

		VisibleComponent->OnComponentHit.AddDynamic(this, &UBallComponent::OnCompHit);
	}

	SetRandomOrientation();
	ThrowObject(throwForce);

	created_ui = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), bp_ui);
	created_ui->AddToViewport();

	if (created_ui) {
		Player1_Score = Cast<UTextBlock>(created_ui->GetWidgetFromName("Player1_Score"));
		Player2_Score = Cast<UTextBlock>(created_ui->GetWidgetFromName("Player2_Score"));

		Player1_Score->SetText(FText::FromString(FString::FromInt(scoreP1)));
		Player2_Score->SetText(FText::FromString(FString::FromInt(scoreP2)));
	}

	GLog->Log("STARTING BALL");
}


// Called every frame
void UBallComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBallComponent::ResetBall()
{
	StopBall();
	SetRandomOrientation();
	ThrowObject(throwForce);
}

void UBallComponent::StopBall()
{
	VisibleComponent->SetPhysicsAngularVelocity(FVector::ZeroVector);
	VisibleComponent->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
	GetOwner()->SetActorLocation(FVector::ZeroVector);
}

void UBallComponent::SetRandomOrientation()
{
	//calculate a random orientation
	float randomAngle = FMath::FRandRange(-180.0f, 180.0f);
	//avoid -180,180,-90,90,0 angles
	float sign = FMath::Sign<float>(randomAngle);
	if (FMath::Abs(randomAngle) < 90.0f)
	{
		randomAngle = sign * FMath::Clamp(FMath::Abs(randomAngle), minimalAngle, 90.0f - minimalAngle);
	}
	else if (FMath::Abs(randomAngle) > 90.0f && FMath::Abs(randomAngle) < 180.0f)
	{
		randomAngle = sign * FMath::Clamp(FMath::Abs(randomAngle), 90.0f + minimalAngle, 180.0f - minimalAngle);
	}
	LOG(FString::SanitizeFloat(randomAngle));
	VisibleComponent->SetWorldRotation(FRotator(0.0f, randomAngle, 0.0f));
}

void UBallComponent::ThrowObject(float power)
{
	if (VisibleComponent)
	{
		VisibleComponent->AddImpulse(VisibleComponent->GetForwardVector() * power);
	}
}

void UBallComponent::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		//prevent the ball from going exclusively horizontally or vertically
		FVector velocity = VisibleComponent->GetPhysicsLinearVelocity();
		float sign1 = FMath::Sign(velocity.X);
		float sign2 = FMath::Sign(velocity.Y);
		VisibleComponent->SetAllPhysicsLinearVelocity(FVector(FMath::Max(FMath::Abs(velocity.X), minimalVelocity) * sign1, FMath::Max(FMath::Abs(velocity.Y), minimalVelocity) * sign2, 0.0f));

		bool goal = false;
		if (OtherActor->ActorHasTag("Goal1"))
		{
			scoreP1 += 1; //scoreToGive is added in globalScore from PawnPlayer.
			Player1_Score->SetText(FText::FromString(FString::FromInt(scoreP1)));
			goal = true;
		}
		else if (OtherActor->ActorHasTag("Goal2"))
		{
			scoreP2 += 1; //scoreToGive is added in globalScore from PawnPlayer.
			Player2_Score->SetText(FText::FromString(FString::FromInt(scoreP2)));
			goal = true;
		}
		else if (OtherActor->ActorHasTag("Player"))
		{
			//manage deviation
		}

		if (goal)
		{
			if (scoreP1 >= 5 || scoreP2 >= 5) {
				scoreP1 = 0;
				scoreP2 = 0;

				created_endgame = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), bp_endgame);
				created_endgame->AddToViewport();

				Winner_Text = Cast<UTextBlock>(created_endgame->GetWidgetFromName("WinnerName"));
				if (scoreP1 >= 5) {
					Winner_Text->SetText(FText::FromString("Player 1 wins"));
					//Winner_Text->;
				}
				else {
					Winner_Text->SetText(FText::FromString("Player 2 wins"));
				}
				

				for (int i = 0; i < players.Num(); i++)
				{
					players[i]->gameOver = true;
				}

				StopBall();
			}
			else {
				ResetBall();
			}
		}
	}
}

