// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHud.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

//constructor for getting all the textblock in the widget, for setting them to cero
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
	GAMEOVER = Cast<UTextBlock>(GetWidgetFromName("GAMEOVER"));
	if (GAMEOVER != nullptr)
	{
		GAMEOVER->SetOpacity(0);
	}
	return true;
}
//static int myValue = 0;

void UGameHud::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

//function for changing the score in the hud
void UGameHud::UpdateScore(int32 score)
{
	this->score = score;
	if (Score != nullptr)
	{
		Score->SetText(FText::FromString("Score: " + FString::FromInt(this->score)));
	}
}

//function for changing the bestscore in the hud
void UGameHud::UpdateBestScore(int32 best)
{
	this->bestScore = best;
	if (BestScore != nullptr)
	{
		BestScore->SetText(FText::FromString("BestScore: " + FString::FromInt(this->bestScore)));
	}
}

//Update lives with number, it can be as well with images
void UGameHud::UpdateLives(int32 live)
{
	this->lives = live;
	if (Live != nullptr)
	{
		Live->SetText(FText::FromString("x " + FString::FromInt(this->lives)));
	}
}

//spawn the game over screen, called from the game mode
void UGameHud::GameOVer()
{
	GAMEOVER->SetOpacity(1);
}
