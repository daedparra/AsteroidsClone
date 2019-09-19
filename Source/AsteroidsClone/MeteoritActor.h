// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeteoritActor.generated.h"


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class Type : uint8
{
	BIG 	UMETA(DisplayName = "Big"),
	MEDIUM 	UMETA(DisplayName = "Medium"),
	SMALL	UMETA(DisplayName = "Small")
};


class URotatingMovementComponent;
class UPaperSpriteComponent;
class UPaperSprite;

UCLASS()
class ASTEROIDSCLONE_API AMeteoritActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		URotatingMovementComponent* RotatingComoponent;

	UPROPERTY(EditAnywhere)
		UPaperSpriteComponent* SpriteComponent;

	

public:	
	// Sets default values for this actor's properties
	AMeteoritActor();
	Type type;
	float Speed;
	FVector MoveDirection;
	TArray<float> RotationPitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoSpawn)
		TArray<float> RotationPitch_USER;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoSpawn)
		TArray<UPaperSprite*> LargeAsteroidsArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoSpawn)
		TArray<UPaperSprite*> MediumAsteroidsArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoSpawn)
		TArray<UPaperSprite*> SmallAsteroidsArray;

	UFUNCTION()
		void SetMeteorit(Type type);

	UFUNCTION()
		void Destroy();

	UFUNCTION()
		void SpawnNew(Type type);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
