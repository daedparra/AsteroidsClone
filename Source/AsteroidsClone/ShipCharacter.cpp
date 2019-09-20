// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipCharacter.h"
#include "Components/InputComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
AShipCharacter::AShipCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComponent->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AShipCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShipCharacter::MoveForward(float Value)
{
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AShipCharacter::MoveRight(float Value)
{

}

// Called every frame
void AShipCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShipCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("HorizontalMovement", this, &AShipCharacter::MoveRight);
	PlayerInputComponent->BindAxis("VerticalMovement", this, &AShipCharacter::MoveForward);
}

