// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipActor.generated.h"

class UPaperSpriteComponent;

UCLASS()
class ASTEROIDSCLONE_API AShipActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		UPaperSpriteComponent* SpriteComponent;
	
public:	
	// Sets default values for this actor's properties
	AShipActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void RotateShipWithMouse();
	UFUNCTION()
		void MoveShip();
	FHitResult HitResult;
	float HitResultTraceDistance;
	bool bMouseInput;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
