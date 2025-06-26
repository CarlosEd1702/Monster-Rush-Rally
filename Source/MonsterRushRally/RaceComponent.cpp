// RaceComponent.cpp
#include "RaceComponent.h"
#include "RaceHUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

URaceComponent::URaceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void URaceComponent::InitPlayerComponent(APlayerController* PC)
{
	PC = Cast<APlayerController>(GetOwner());
	if (PC && RaceHUDWidgetClass)
	{
		RaceHUD = CreateWidget<URaceHUDWidget>(PC, RaceHUDWidgetClass);
		if (RaceHUD)
		{
			RaceHUD->AddToPlayerScreen();
			RaceHUD->UpdateRaceHUD(RaceTime, CurrentLap, TotalLaps, CurrentCheckpoint, TotalCheckpoints, Position);
			PlayerHUDs.Add(PC, RaceHUD);

			if (PC->HasAuthority())
			{
				GetWorld()->GetTimerManager().SetTimer(
					RaceTimerHandle,
					this,
					&URaceComponent::UpdateRaceTime,
					0.1f,
					true
				);
			}
		}
	}
}

void URaceComponent::StartRace(float ServerStartTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Race Started at: %f"), ServerStartTime);

	// Evento Blueprint opcional para mostrar UI, countdown, etc.
	OnRaceStart();
}

void URaceComponent::OnRaceProgress(APlayerController* PC, float NewTime, int32 NewLap, int32 NewPosition)
{
	if (bRaceFinished) return;

	CurrentLap = NewLap;
	CurrentCheckpoint++;
	Position = NewPosition;

	if (CurrentLap == TotalLaps)
	{
		bRaceFinished = true;

		if (RaceHUD)
		{
			RaceHUD->SetRaceFinished();
		}

		GetWorld()->GetTimerManager().ClearTimer(RaceTimerHandle);
	}
}

void URaceComponent::SetupRace(int32 InTotalLaps, int32 InTotalCheckpoints)
{
	TotalLaps = InTotalLaps;
	TotalCheckpoints = InTotalCheckpoints;
}

void URaceComponent::UpdatePlayerPosition(int32 NewPosition)
{
	Position = NewPosition;
}

void URaceComponent::SetPosition(int32 NewPosition)
{
	Position = NewPosition;
}

int32 URaceComponent::GetProgressScore() const
{
	return (CurrentLap * 1000) + CurrentCheckpoint;
}

void URaceComponent::AdvanceCheckpoint()
{
	CurrentCheckpoint++;
}

void URaceComponent::AdvanceLap()
{
	CurrentLap++;
}

void URaceComponent::ResetCheckpoint()
{
	CurrentCheckpoint = 0;
}

void URaceComponent::OnRep_UpdateHUD()
{
	if (RaceHUD)
	{
		RaceHUD->UpdateRaceHUD(RaceTime, CurrentLap, TotalLaps, CurrentCheckpoint, TotalCheckpoints, Position);
	}
}

void URaceComponent::UpdateRaceTime()
{
	RaceTime += 0.1f;

	if (RaceHUD)
	{
		RaceHUD->UpdateRaceHUD(RaceTime, CurrentLap, TotalLaps, CurrentCheckpoint, TotalCheckpoints, Position);
	}
}

void URaceComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URaceComponent, CurrentLap);
	DOREPLIFETIME(URaceComponent, CurrentCheckpoint);
	DOREPLIFETIME(URaceComponent, Position);
	DOREPLIFETIME(URaceComponent, RaceTime);
}