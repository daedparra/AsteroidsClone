// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHud.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

bool UGameHud::Initialize()
{
	bool bResult = Super::Initialize();
	if (!bResult)
	{
		return false;
	}
	Score = Cast<UTextBlock>(GetWidgetFromName("Score"));
	if (Score != nullptr)
	{
		Score->SetText(FText::FromString("Score: 0"));
	}
	BestScore = Cast<UTextBlock>(GetWidgetFromName("BestScore"));
	if (BestScore != nullptr)
	{
		BestScore->SetText(FText::FromString("BestScore: 0"));
	}
	Live = Cast<UTextBlock>(GetWidgetFromName("Live"));
	if (Live != nullptr)
	{
		Live->SetText(FText::FromString("x 3"));
	}
	return true;
}
//static int myValue = 0;

void UGameHud::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UGameHud::UpdateScore(float score)
{
	this->score = score;
	if (Score != nullptr)
	{
		Score->SetText(FText::FromString("Score: " + FString::SanitizeFloat(this->score)));
	}
}

void UGameHud::UpdateBestScore(float best)
{
	this->bestScore = best;
	if (BestScore != nullptr)
	{
		BestScore->SetText(FText::FromString("BestScore: 0" + FString::SanitizeFloat(this->bestScore)));
	}
}

void UGameHud::UpdateLives(float live)
{
	this->lives = live;
	if (Live != nullptr)
	{
		Live->SetText(FText::FromString("x " + FString::SanitizeFloat(this->lives)));
	}
}
