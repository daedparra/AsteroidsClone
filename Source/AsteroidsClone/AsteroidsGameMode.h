// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AsteroidsGameMode.generated.h"

/**
 * 
 */
class UUserWidget;
class AMeteoritActor;
class USaveGameData;
class AShipActor;
UCLASS()
class ASTEROIDSCLONE_API AAsteroidsGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AAsteroidsGameMode();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoSpawn)
		int32 X_Max_USER = 400;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoSpawn)
		int32 Z_Max_USER = 400;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoSpawn)
		int32 Score_USER = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoSpawn)
		int32 Lives_USER = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoSpawn)
	TArray<float> SpawnAngles_USER;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoSpawn)
	UUserWidget* Hud_Ref;*/



private:

	UFUNCTION()
		void SpawnMeteorit();

	UFUNCTION()
		void CheckSaveGame();

	UFUNCTION()
		void UpdateScore(int32 Bonus);

	UFUNCTION()
		void TryToSpawnPlayer();

	TArray<float> SpawnPoints_Temporal;
	int32 X_Max;
	int32 Z_Max;
	TArray<float> SpawnAngles;
	int32 Score;
	int32 Lives;
	USaveGameData* SaveGameRef;
	TSubclassOf<AMeteoritActor> Meteiorit;
	TSubclassOf<AShipActor> ShipPlayer;
};
