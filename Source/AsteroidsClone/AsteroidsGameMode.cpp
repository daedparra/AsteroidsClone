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
#include "GameHud.h"

AAsteroidsGameMode::AAsteroidsGameMode() 
{
	static ConstructorHelpers::FClassFinder<AActor> BP_Meteorit(TEXT("/Game/Blueprints/BP_MeteoritActor"));
	Meteiorit = BP_Meteorit.Class;
}

void AAsteroidsGameMode::BeginPlay() 
{
	X_Max = X_Max_USER;
	Z_Max = Z_Max_USER;
	Lives = Lives_USER;
	Score = Score_USER;
	SpawnAngles = SpawnAngles_USER;
	SpawnMeteorit();
	FTimerDelegate TimerR;
	FTimerHandle TimerHR;
	TimerR.BindUFunction(this, FName("SpawnMeteorit"));
	GetWorldTimerManager().SetTimer(TimerHR, TimerR, FMath::RandRange(6.0f,10.0f), true);
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	GameInfoWidget = CreateWidget<UGameHud>(PC, Hud_Ref);
	GameInfoWidget->AddToViewport();
	CheckSaveGame();
}

void AAsteroidsGameMode::SpawnMeteorit()
{
	SpawnPoints_Temporal = SpawnAngles;
	int32 LastIndex = FMath::RandRange(MinNumberofMeteorits, MaxNumberofMeteorits);
	for (size_t i = 0; i < LastIndex; i++)
	{
		SpawnPoints_Temporal.Sort([this](const int Item1, const int Item2) {
			return FMath::FRand() < 0.5f;
		});
		int32 j = FMath::RandRange(0, SpawnPoints_Temporal.Num() - 1 );
		FVector res = FVector(X_Max, 0.0f, Z_Max);
		FVector result = res.RotateAngleAxis(SpawnPoints_Temporal[j], FVector(0.0f, 1.0f, 0.0f));

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.Owner = this;
		FVector SpawnLocation = result;
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
		GameInfoWidget->UpdateBestScore(SaveGameRef->BestScore);
	}
	else {
		USaveGameData* SaveGameInstance = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
		SaveGameRef = SaveGameInstance;
		SaveGameRef->BestScore = 0;
		GameInfoWidget->UpdateBestScore(SaveGameRef->BestScore);
		UGameplayStatics::SaveGameToSlot(SaveGameRef, SaveGameRef->SaveSlotName, SaveGameRef->UserIndex);
	}
}

void AAsteroidsGameMode::UpdateScore(int32 Bonus)
{
	Score += Bonus;
	GameInfoWidget->UpdateScore(Score);
}

//will be call after one second
void AAsteroidsGameMode::TryToSpawnPlayer()
{
	Lives -= 1;
	GameInfoWidget->UpdateLives(Lives);
	if (Lives < 1) 
	{
		//call game over event
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PC->SetPause(true);
		GameInfoWidget->GameOVer();
		USaveGameData* LoadGameInstance = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
		LoadGameInstance = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
		if (LoadGameInstance != nullptr)
		{
			SaveGameRef = LoadGameInstance;
			if (SaveGameRef->BestScore <= Score) 
			{
				SaveGameRef->BestScore = Score;
				GameInfoWidget->UpdateBestScore(SaveGameRef->BestScore);
			}
			UGameplayStatics::SaveGameToSlot(SaveGameRef, SaveGameRef->SaveSlotName, SaveGameRef->UserIndex);
		}
	}
}
