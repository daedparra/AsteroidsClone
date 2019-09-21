// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipPawn.h"
#include "Components/InputComponent.h"
#include "PaperSpriteComponent.h"
#include "Math/UnrealMathUtility.h"
#include "AsteroidsGameMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MissileActor.h"
#include "Engine.h"
#include "MeteoritActor.h"
#include "Explosion.h"

// Sets default values
AShipPawn::AShipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComponent->AttachTo(RootComponent);
	SpriteComponent->OnComponentBeginOverlap.AddDynamic(this, &AShipPawn::OnOverlapBegin);
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void AShipPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMeteoritActor>(OtherActor)) 
	{
		if (UPrimitiveComponent* PrimitiveComponent = FindComponentByClass<UPrimitiveComponent>())
		{
			PrimitiveComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		}
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.Owner = this;
		FVector location = GetActorLocation();
		FVector SpawnLocation = FVector(location.X, location.Y + 10.0f, location.Z);
		FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
		AExplosion* SpawnedExplosion = Cast<AExplosion>(GetWorld()->SpawnActor(Explosion, &SpawnLocation, &SpawnRotation, SpawnInfo));
		AAsteroidsGameMode* gm = Cast<AAsteroidsGameMode>(GetWorld()->GetAuthGameMode());
		gm->TryToSpawnPlayer();
		FTimerDelegate TimerR;
		FTimerHandle TimerHR;
		TimerR.BindUFunction(this, FName("CollsionBack"));
		GetWorldTimerManager().SetTimer(TimerHR, TimerR, 2.0, false);
		SetActorLocation(FVector(0, 0, 0));
	}
}

void AShipPawn::checkBounderies()
{
	AAsteroidsGameMode* gm = Cast<AAsteroidsGameMode>(GetWorld()->GetAuthGameMode());
	if (abs(GetActorLocation().X) > gm->X_Max)
	{
		float value = UKismetMathLibrary::SignOfFloat(GetActorLocation().X);
		value *= -1;
		value *= (gm->X_Max - 20);
		FVector result = FVector(value, GetActorLocation().Y, GetActorLocation().Z);
		SetActorLocation(result);
	}
	if (abs(GetActorLocation().Z) > gm->Z_Max)
	{
		float value = UKismetMathLibrary::SignOfFloat(GetActorLocation().Z);
		value *= -1;
		value *= (gm->Z_Max - 20);
		FVector result = FVector(GetActorLocation().X, GetActorLocation().Y, value);
		SetActorLocation(result);
	}
}

void AShipPawn::MoveShip(float DeltaTime)
{
	FVector face = FVector(HMovement, 0.f, VMovement);
	FVector faceN = face;
	faceN.Normalize();
	FVector Mult = faceN * Speed * DeltaTime;
	FVector target;
	float InterpSpeed;
	if (face.Size() > 0.0)
	{
		target = Mult;
		InterpSpeed = 5.0;
	}
	else
	{
		target = FVector(0, 0, 0);
		InterpSpeed = 1.0;
	}
	FVector result = FMath::VInterpTo(MotionVectorTemp, target, DeltaTime, InterpSpeed);
	MotionVectorTemp = result;
	AddActorWorldOffset(MotionVectorTemp);
}

void AShipPawn::fireTimer()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.Owner = this;
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	AMissileActor* SpawnedMissile = Cast<AMissileActor>(GetWorld()->SpawnActor(Missile, &SpawnLocation, &SpawnRotation, SpawnInfo));
	if(SpawnedMissile != nullptr) SpawnedMissile->ProjectileMovementComponent->SetVelocityInLocalSpace(FVector(1200, 0, 0));
}

void AShipPawn::CollsionBack()
{
	if (UPrimitiveComponent* PrimitiveComponent = FindComponentByClass<UPrimitiveComponent>())
	{
		PrimitiveComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	}
}

// Called when the game starts or when spawned
void AShipPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShipPawn::MoveForward(float Value)
{
	VMovement = Value;
}

void AShipPawn::MoveRight(float Value)
{
	HMovement = Value;
}

void AShipPawn::Fire()
{

	FTimerDelegate TimerR;
	FTimerHandle TimerHR;
	TimerR.BindUFunction(this, FName("fireTimer"));
	GetWorldTimerManager().SetTimer(TimerHR, TimerR, 0.3, false);
}

// Called every frame
void AShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveShip(DeltaTime);
	checkBounderies();
}

// Called to bind functionality to input
void AShipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("HorizontalMovement", this, &AShipPawn::MoveRight);
	PlayerInputComponent->BindAxis("VerticalMovement", this, &AShipPawn::MoveForward);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShipPawn::Fire);
}

