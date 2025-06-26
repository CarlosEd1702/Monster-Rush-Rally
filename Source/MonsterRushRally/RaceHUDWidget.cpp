// RaceHUDWidget.cpp

#include "RaceHUDWidget.h"
#include "Components/TextBlock.h"

void URaceHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Puede inicializar valores por defecto aquí si gustas
}

void URaceHUDWidget::UpdateRaceHUD(float RaceTime, int32 CurrentLap, int32 TotalLaps,
		int32 CurrentCheckpoint, int32 TotalCheckpoints, int32 Position)
{
	if (Text_RaceTime)
	{
		int32 Minutes = FMath::FloorToInt(RaceTime / 60.f);
		int32 Seconds = FMath::FloorToInt(FMath::Fmod(RaceTime, 60.f));
		Text_RaceTime->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
	}

	if (Text_CurrentLap)
	{
		Text_CurrentLap->SetText(FText::AsNumber(CurrentLap));
	}

	if(Text_TotalLaps)
	{
		Text_TotalLaps->SetText(FText::AsNumber(TotalLaps));
	}

	if(Text_CurrentCheckpoint)
	{
		Text_CurrentCheckpoint->SetText(FText::AsNumber(CurrentCheckpoint));
	}

	if(Text_TotalCheckpoints)
	{
		Text_TotalCheckpoints->SetText(FText::AsNumber(TotalCheckpoints));
	}

	if (Text_Position)
	{
		Text_Position->SetText(FText::AsNumber(Position));
	}
}
