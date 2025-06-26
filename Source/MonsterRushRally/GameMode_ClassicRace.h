#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_ClassicRace.generated.h"

class URaceComponent;
class APlayerController;

UCLASS()
class MONSTERRUSHRALLY_API AGameMode_ClassicRace : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameMode_ClassicRace();

	virtual void BeginPlay() override;

	// Llamado por el RaceComponent cuanto el HUD ya esta listo
	UFUNCTION(BlueprintCallable)
	void NotifyHUDReady(APlayerController* PC);

	UFUNCTION(BlueprintCallable, Category = "Init Components")
	void InitPlayerComponent(APlayerController* PC);

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void OnPlayerCheckpoint(APlayerController* PC, int32 NewLap);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Race Settings")
	int32 TotalLaps = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Race Settings")
	int32 TotalCheckpoints = 6;

protected:
	UPROPERTY()
	TArray<APlayerController*> LocalPlayers;
	
	UPROPERTY()
	TArray<URaceComponent*> LocalRaceComponents;

	UFUNCTION()
	void StartCountdown();

	UFUNCTION()
	void StartRace();

	UFUNCTION()
	void UpdatePlayerPositions();

private:
	int32 PlayersReady = 0;
	FTimerHandle CountdownTimer;
	float RaceStartTime = 0.0f;

};
