// Fill out your copyright notice in the Description page of Project Settings.

#include "Explosion.h"
#include "PaperFlipbookComponent.h"

// Sets default values
AExplosion::AExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create the sprite for the BP to select an image
	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	SpriteComponent->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AExplosion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//setting a life spawn for getting destroy over a time
	time -= DeltaTime;
	if (time < 0) Destroy();
}

