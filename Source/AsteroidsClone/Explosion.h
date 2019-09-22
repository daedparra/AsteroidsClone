// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Explosion.generated.h"

class UPaperFlipbookComponent;
UCLASS()
class ASTEROIDSCLONE_API AExplosion : public AActor
{
	GENERATED_BODY()
	//property for the sprite
	UPROPERTY(EditAnywhere)
		UPaperFlipbookComponent* SpriteComponent;
public:	
	// Sets default values for this actor's properties
	AExplosion();
	float time = 1.0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
