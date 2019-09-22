// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHud.generated.h"

/**
 * 
 */
class UTextBlock;
UCLASS()
class ASTEROIDSCLONE_API UGameHud : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:

	UFUNCTION()
		void UpdateScore(int32 score);
	UFUNCTION()
		void UpdateBestScore(int32 best);
	UFUNCTION()
		void UpdateLives(int32 live);
	UFUNCTION()
		void GameOVer();
private:
	//variables of score, best and live, for the hud
	int32 score = 0;
	int32 bestScore = 0;
	int32 lives = 0;
	UTextBlock* Score;
	UTextBlock* BestScore;
	UTextBlock* Live;
	UTextBlock* GAMEOVER;
};
