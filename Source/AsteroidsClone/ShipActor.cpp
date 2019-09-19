// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipActor.h"

// Sets default values
AShipActor::AShipActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShipActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShipActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

