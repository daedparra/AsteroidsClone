// Fill out your copyright notice in the Description page of Project Settings.

#include "AsteroidsGameMode.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"
#include "Blueprint/UserWidget.h"
#include "MeteoritActor.h"
#include "SaveGameData.h"
#include "ShipActor.h"

AAsteroidsGameMode::AAsteroidsGameMode() 
{
	X_Max = X_Max_USER;
	Z_Max = Z_Max_USER;
	Lives = Lives_USER;
	Score = Score_USER;
	SpawnAngles = SpawnAngles_USER;

	static ConstructorHelpers::FClassFinder<AActor> BP_Meteorit(TEXT("/Game/Blueprints/BP_MeteoritActor"));
	Meteiorit = BP_Meteorit.Class;
}

void AAsteroidsGameMode::BeginPlay() 
{
	SpawnMeteorit();
	FTimerDelegate TimerR;
	FTimerHandle TimerHR;
	TimerR.BindUFunction(this, FName("SpawnMeteorit"));
	GetWorldTimerManager().SetTimer(TimerHR, TimerR, FMath::RandRange(6.0f,10.0f), true);
	//Hud_Ref->AddToViewport(9999); // Z-order, this just makes it render on the very top.
	CheckSaveGame();
}

void AAsteroidsGameMode::SpawnMeteorit()
{
	SpawnPoints_Temporal = SpawnAngles;
	int32 LastIndex = FMath::RandRange(3, 5);
	for (size_t i = 0; i < LastIndex; i++)
	{
		SpawnPoints_Temporal.Sort([this](const int Item1, const int Item2) {
			return FMath::FRand() < 0.5f;
		});
		int32 j = FMath::FloorToInt(FMath::SRand() * (i + 1)) % SpawnPoints_Temporal.Num();
		FVector res = FVector(X_Max, 0.0f, Z_Max);
		res.RotateAngleAxis(SpawnPoints_Temporal[j], FVector(0.0f, 1.0f, 0.0f));

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.Owner = this;
		FVector SpawnLocation = res;
		FRotator SpawnRotation = FRotator(0,0,0);
		AMeteoritActor* SpawnedMeteorit = Cast<AMeteoritActor>(GetWorld()->SpawnActor(Meteiorit, &SpawnLocation, &SpawnRotation, SpawnInfo));
		SpawnedMeteorit->type = Type::BIG;
		SpawnedMeteorit->SetMeteorit(Type::BIG);
	}
}

void AAsteroidsGameMode::CheckSaveGame()
{
	USaveGameData* LoadGameInstance = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
	LoadGameInstance = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	if (LoadGameInstance != nullptr)
	{
		SaveGameRef = LoadGameInstance;
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Best Score:" +  FString::FromInt(SaveGameRef->BestScore));
			//Add to hud
		}
	}
	else {
		USaveGameData* SaveGameInstance = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
		SaveGameRef = SaveGameInstance;
		SaveGameRef->BestScore = 0;
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Best Score:" + FString::FromInt(SaveGameRef->BestScore));
			//Add to hud
		}
		UGameplayStatics::SaveGameToSlot(SaveGameRef, SaveGameRef->SaveSlotName, SaveGameRef->UserIndex);
	}
}

void AAsteroidsGameMode::UpdateScore(int32 Bonus)
{
	Score += Bonus;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, "Score:" + FString::FromInt(Score));
		//Add to hud
	}
}

//will be call after one second
void AAsteroidsGameMode::TryToSpawnPlayer()
{
	Lives -= 1;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, "Lives:" + FString::FromInt(Lives));
		//Add to hud for function update lives
	}
	if (Lives > 1) 
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.Owner = this;
		FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);
		FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
		AShipActor* SpawnedShip = Cast<AShipActor>(GetWorld()->SpawnActor(ShipPlayer, &SpawnLocation, &SpawnRotation, SpawnInfo));
	}
	else 
	{
		//call game over event
		USaveGameData* LoadGameInstance = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
		LoadGameInstance = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
		if (LoadGameInstance != nullptr)
		{
			SaveGameRef = LoadGameInstance;
			if (SaveGameRef->BestScore <= Score) 
			{
				SaveGameRef->BestScore = Score;
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Best Score:" + FString::FromInt(SaveGameRef->BestScore));
					//Add to hud
				}
				UGameplayStatics::SaveGameToSlot(SaveGameRef, SaveGameRef->SaveSlotName, SaveGameRef->UserIndex);
			}
		}
	}
}
