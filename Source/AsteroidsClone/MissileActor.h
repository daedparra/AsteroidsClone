// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MissileActor.generated.h"

class UPaperSpriteComponent;
UCLASS()
class ASTEROIDSCLONE_API AMissileActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		UPaperSpriteComponent* SpriteComponent;
	
	
	
public:	
	// Sets default values for this actor's properties
	AMissileActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		float Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Movement")
		UProjectileMovementComponent* ProjectileMovementComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
