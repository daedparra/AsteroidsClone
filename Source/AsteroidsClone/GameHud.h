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
		void UpdateScore(float score);
	UFUNCTION()
		void UpdateBestScore(float best);
	UFUNCTION()
		void UpdateLives(float live);

private:
	float score = 0.0f;
	float bestScore = 0.0f;
	float lives = 0.0f;
	UTextBlock* Score;
	UTextBlock* BestScore;
	UTextBlock* Live;
};
