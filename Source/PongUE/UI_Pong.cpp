// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Pong.h"

// Sets default values
AUI_Pong::AUI_Pong()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUI_Pong::BeginPlay()
{
	Super::BeginPlay();
	
	created_ui = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), bp_ui);
	created_ui->AddToViewport();

	//text = Cast<UTextBlock>(created_ui->GetWidgetFromName(TEXT("MyText")));
	//text->SetText(FText::FromString("Hello World"));
	//text->SetColorAndOpacity(FSlateColor(FLinearColor::Blue));
}

// Called every frame
void AUI_Pong::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

