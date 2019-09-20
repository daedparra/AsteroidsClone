// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipActor.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperSpriteComponent.h"
#include "Engine/LocalPlayer.h"

// Sets default values
AShipActor::AShipActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	RootComponent = SpriteComponent;
}

// Called when the game starts or when spawned
void AShipActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShipActor::RotateShipWithMouse()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bool hitResult = PC->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);
	if (hitResult || !hitResult) 
	{
		FVector res = FVector(HitResult.Location.X, 0.0f, HitResult.Location.Z);
		res -= GetActorLocation();
		res.Normalize();
		float dotp = FVector::DotProduct(res, FVector(0.0, 0.0, 1.0));
		float coseno = acos(dotp);
		float dotp2 = FVector::DotProduct(res, FVector(-1.0, 0.0, 0.0));
		float value = UKismetMathLibrary::SignOfFloat(dotp2);
		FRotator res1;
		res1.Roll = 0;
		res1.Yaw = 0;
		res1.Pitch = coseno * value;
		SetActorRotation(res1);
	}
}

void AShipActor::MoveShip()
{
}

// Called every frame
void AShipActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//RotateShipWithMouse();
}

