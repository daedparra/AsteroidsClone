// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShipCharacter.generated.h"

class UPaperSpriteComponent;
UCLASS()
class ASTEROIDSCLONE_API AShipCharacter : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
		UPaperSpriteComponent* SpriteComponent;

public:
	// Sets default values for this character's properties
	AShipCharacter();
	void MoveForward(float Value);
	void MoveRight(float Value);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
