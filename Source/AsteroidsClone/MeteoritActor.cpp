// Fill out your copyright notice in the Description page of Project Settings.

#include "MeteoritActor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Engine.h"
#include "AsteroidsGameMode.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

// Sets default values
AMeteoritActor::AMeteoritActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

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
	RotatingComoponent->RotationRate.Pitch = RotationPitch[randomvalue];
	if (type == Type::BIG) 
	{
		int32 j = FMath::RandRange(0, LargeAsteroidsArray.Num() -1 );
		SpriteComponent->SetSprite(LargeAsteroidsArray[j]);
		FVector vector = FVector(FMath::RandRange(-300.0f, 300.0f),0.0f, FMath::RandRange(-80.0f, 80.0f));
		vector -= GetActorLocation();
		//vector.GetSafeNormal();
		vector.Normalize();
		MoveDirection = vector;
		Speed = FMath::RandRange(60.0f, 80.0f);
	}else if (type == Type::MEDIUM)
	{
		int32 j = FMath::RandRange(0, MediumAsteroidsArray.Num() - 1 );
		SpriteComponent->SetSprite(MediumAsteroidsArray[j]);
		FVector vector = FVector(FMath::RandRange(-1.0f, 1.0f), 0.0f, FMath::RandRange(-1.0f, 1.0f));
		vector.Normalize();
		MoveDirection = vector;
		Speed = FMath::RandRange(90.0f, 110.0f);
	}else if (type == Type::SMALL)
	{
		int32 j = FMath::RandRange(0, SmallAsteroidsArray.Num() -1 );
		SpriteComponent->SetSprite(SmallAsteroidsArray[j]);
		FVector vector = FVector(FMath::RandRange(-300.0f, 300.0f), 0.0f, FMath::RandRange(-80.0f, 80.0f));
		vector.Normalize();
		MoveDirection = vector;
		Speed = FMath::RandRange(120.0f, 140.0f);
	}
}

void AMeteoritActor::Destroy()
{
	AAsteroidsGameMode* gm = Cast<AAsteroidsGameMode>(GetWorld()->GetAuthGameMode());
	if (type == Type::BIG)
	{
		gm->UpdateScore(10);
		SpawnNew(Type::MEDIUM);
		Destroy();
	}
	if (type == Type::MEDIUM)
	{
		gm->UpdateScore(50);
		SpawnNew(Type::SMALL);
		Destroy();
	}
	if (type == Type::SMALL)
	{
		gm->UpdateScore(100);
		Destroy();
	}
}

void AMeteoritActor::SpawnNew(Type type)
{
	for (size_t i = 0; i < 2; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.Owner = this;
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = FRotator(0, 0, 0);
		AMeteoritActor* SpawnedMeteorit = Cast<AMeteoritActor>(GetWorld()->SpawnActor(AMeteoritActor::GetClass() , &SpawnLocation, &SpawnRotation, SpawnInfo));
		SpawnedMeteorit->type = type;
		SpawnedMeteorit->SetMeteorit(type);
	}
}

// Called when the game starts or when spawned
void AMeteoritActor::BeginPlay()
{
	Super::BeginPlay();
	RotationPitch = RotationPitch_USER;
}

// Called every frame
void AMeteoritActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(MoveDirection * Speed * DeltaTime);
}

