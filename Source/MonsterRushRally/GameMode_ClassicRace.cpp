#include "GameMode_ClassicRace.h"
#include "GameFramework/PlayerController.h"
#include "RaceComponent.h"
#include "TimerManager.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AGameMode_ClassicRace::AGameMode_ClassicRace()
{
	// Default config
}

void AGameMode_ClassicRace::BeginPlay()
{
	Super::BeginPlay();

	const int32 NumPlayers = GetGameInstance()->GetNumLocalPlayers();

	// Crear jugadores locales si no están creados
	for (int32 i = 1; i < NumPlayers; ++i)
	{
		UGameplayStatics::CreatePlayer(this, i);
	}

	// Recoger PlayerControllers y llamar InitPlayerComponent
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC)
		{
			LocalPlayers.Add(PC);
			if (APawn* Pawn = PC->GetPawn())
			{
				if (URaceComponent* RaceComp = Pawn->FindComponentByClass<URaceComponent>())
				{
					RaceComp->InitPlayerComponent(PC);
				}
			}
		}
	}
}

void AGameMode_ClassicRace::NotifyHUDReady(APlayerController* PC)
{
	PlayersReady++;

	if (PlayersReady >= LocalPlayers.Num())
	{
		StartCountdown();
	}
}

void AGameMode_ClassicRace::InitPlayerComponent(APlayerController* PC)
{
	if (!PC) return;

	URaceComponent* RaceComp = NewObject<URaceComponent>(PC, URaceComponent::StaticClass());
	if (RaceComp)
	{
		RaceComp->RegisterComponent();
		PC->AddInstanceComponent(RaceComp);

		RaceComp->SetupRace(TotalLaps, TotalCheckpoints);
		RaceComp->InitPlayerComponent(PC);
		LocalPlayers.Add(PC);
		LocalRaceComponents.Add(RaceComp);
	}
}

void AGameMode_ClassicRace::OnPlayerCheckpoint(APlayerController* PC, int32 NewLap)
{
	if (!PC) return;

	if (URaceComponent* RaceComp = PC->FindComponentByClass<URaceComponent>())
	{
		if (NewLap > RaceComp->GetCurrentLap())
		{
			RaceComp->AdvanceLap();
			RaceComp->ResetCheckpoint();
		}
		else
		{
			RaceComp->AdvanceCheckpoint();
		}
	}

	UpdatePlayerPositions();
}

void AGameMode_ClassicRace::StartCountdown()
{
	// Este es un ejemplo: deberías mostrar una UI real que maneje esto
	GetWorld()->GetTimerManager().SetTimer(CountdownTimer, this, &AGameMode_ClassicRace::StartRace, 3.0f, false);
}

void AGameMode_ClassicRace::StartRace()
{
	RaceStartTime = GetWorld()->GetTimeSeconds();

	for (APlayerController* PC : LocalPlayers)
	{
		if (PC)
		{
			PC->SetIgnoreMoveInput(false);

			if (APawn* Pawn = PC->GetPawn())
			{
				if (URaceComponent* RaceComp = Pawn->FindComponentByClass<URaceComponent>())
				{
					RaceComp->StartRace(RaceStartTime);
				}
			}
		}
	}
}

void AGameMode_ClassicRace::UpdatePlayerPositions()
{
	TArray<APlayerController*> Players;

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		if (APlayerController* PC = It->Get())
		{
			Players.Add(PC);
		}
	}

	Players.Sort([](const APlayerController& A, const APlayerController& B)
	{
		const URaceComponent* CompA = A.FindComponentByClass<URaceComponent>();
		const URaceComponent* CompB = B.FindComponentByClass<URaceComponent>();

		if (!CompA || !CompB) return false;

		return CompA->GetProgressScore() > CompB->GetProgressScore();
	});

	for (int32 i = 0; i < Players.Num(); ++i)
	{
		APlayerController* PC = Players[i];
		if (URaceComponent* RC = PC->FindComponentByClass<URaceComponent>())
		{
			RC->SetPosition(i + 1);
			// HUD se actualiza por replicación o OnRep
		}
	}
}
