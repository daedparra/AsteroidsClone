// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShipPawn.generated.h"

class UPaperSpriteComponent;
class AMissileActor;
class AExplosion;
UCLASS()
class ASTEROIDSCLONE_API AShipPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShipPawn();

	UPROPERTY(EditAnywhere)
		UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoSpawn)
		TSubclassOf<AExplosion> Explosion;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Fire();

	float HMovement;
	float VMovement; 

	FVector MotionVectorTemp;
	float Speed  = 200;

	UFUNCTION()
		void checkBounderies();
	UFUNCTION()
		void MoveShip(float DeltaTime);
	UFUNCTION()
		void fireTimer();
	UFUNCTION()
		void CollsionBack();

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoSpawn)
		TSubclassOf<AMissileActor> Missile;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
