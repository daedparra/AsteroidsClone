// Fill out your copyright notice in the Description page of Project Settings.

#include "MeteoritActor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

// Sets default values
AMeteoritActor::AMeteoritActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RotationPitch = RotationPitch_USER;

	// Create movement component and set rotation rate
	RotatingComoponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingComponent"));
	RotatingComoponent->RotationRate = FRotator(0, 0, 0);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComponent->AttachTo(RootComponent);
}

void AMeteoritActor::SetMeteorit(Type type)
{
	this->type = type;
	int randomvalue = FMath::RandRange(0, 3);
	RotatingComoponent->RotationRate = FRotator(0, RotationPitch[randomvalue], 0);
	if (type == Type::BIG) 
	{
		int32 j = FMath::FloorToInt(FMath::SRand() * (1)) % LargeAsteroidsArray.Num();
		SpriteComponent->SetSprite(LargeAsteroidsArray[j]);
		FVector vector = FVector(FMath::RandRange(-300.0f, 300.0f),0.0f, FMath::RandRange(-80.0f, 80.0f));
		vector -= GetActorLocation();
		vector.Normalize();
		MoveDirection = vector;
		Speed = FMath::RandRange(60.0f, 80.0f);
	}else if (type == Type::MEDIUM)
	{
		int32 j = FMath::FloorToInt(FMath::SRand() * (1)) % MediumAsteroidsArray.Num();
		SpriteComponent->SetSprite(MediumAsteroidsArray[j]);
		FVector vector = FVector(FMath::RandRange(-1.0f, 1.0f), 0.0f, FMath::RandRange(-1.0f, 1.0f));
		vector.Normalize();
		MoveDirection = vector;
		Speed = FMath::RandRange(90.0f, 110.0f);
	}else if (type == Type::SMALL)
	{
		int32 j = FMath::FloorToInt(FMath::SRand() * (1)) % SmallAsteroidsArray.Num();
		SpriteComponent->SetSprite(SmallAsteroidsArray[j]);
		FVector vector = FVector(FMath::RandRange(-300.0f, 300.0f), 0.0f, FMath::RandRange(-80.0f, 80.0f));
		vector.Normalize();
		MoveDirection = vector;
		Speed = FMath::RandRange(120.0f, 140.0f);
	}
}

void AMeteoritActor::Destroy()
{
}

void AMeteoritActor::SpawnNew(Type type)
{
}

// Called when the game starts or when spawned
void AMeteoritActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeteoritActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Speed *= DeltaTime;
	MoveDirection *= Speed;
	AddActorWorldOffset(MoveDirection);

}

