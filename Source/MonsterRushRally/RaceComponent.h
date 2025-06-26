#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayModeInterface.h"
#include "RaceComponent.generated.h"

class URaceHUDWidget;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MONSTERRUSHRALLY_API URaceComponent : public UActorComponent, public IGameplayModeInterface
{
	GENERATED_BODY()

public:
	URaceComponent();

	UFUNCTION(BlueprintCallable)
	virtual void InitPlayerComponent(APlayerController* PC) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void OnRaceProgress(APlayerController* PC, float NewTime, int32 NewLap, int32 NewPosition) override;

	UFUNCTION(BlueprintCallable)
	void StartRace(float ServerStartTime);

	void SetupRace(int32 InTotalLaps, int32 InTotalCheckpoints);

	UFUNCTION(BlueprintCallable, Category = "Lap")
	int32 GetCurrentLap() const { return CurrentLap; }

	UFUNCTION(BlueprintCallable, Category = "Lap")
	int32 GetTotalLaps() const { return TotalLaps; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lap")
	int32 TotalLaps = 3;

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	int32 GetCurrentCheckpoint() const { return CurrentCheckpoint; }

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	int32 GetTotalCheckpoints() const { return TotalCheckpoints; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Checkpoint")
	int32 TotalCheckpoints = 6;

	UFUNCTION(BlueprintCallable, Category = "Time")
	float GetRaceTime() const { return RaceTime; }

	UFUNCTION(BlueprintCallable, Category = "Position")
	int32 GetPosition() const { return Position; }

	void UpdatePlayerPosition(int32 NewPosition);
	int32 GetProgressScore() const;
	void SetPosition(int32 NewPosition);

	bool bRaceFinished = false;
	bool HasFinishedRace() const { return bRaceFinished; }

	UFUNCTION(BlueprintCallable, Category = "Race")
	void AdvanceCheckpoint();

	UFUNCTION(BlueprintCallable, Category = "Race")
	void AdvanceLap();

	UFUNCTION(BlueprintCallable, Category = "Race")
	void ResetCheckpoint();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> RaceHUDWidgetClass;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	URaceHUDWidget* GetHUDForPlayer(APlayerController* PlayerController) const
	{
		if (PlayerHUDs.Contains(PlayerController))
		{
			return PlayerHUDs[PlayerController];
		}
		return nullptr;
	}

	UFUNCTION(BlueprintImplementableEvent, Category = "Race")
	void OnRaceStart();

protected:
	
	FTimerHandle RaceTimerHandle;

	UPROPERTY(ReplicatedUsing=OnRep_UpdateHUD)
	int32 CurrentLap = 1;

	UPROPERTY(ReplicatedUsing=OnRep_UpdateHUD)
	int32 CurrentCheckpoint = 0;

	UPROPERTY(ReplicatedUsing=OnRep_UpdateHUD)
	int32 Position = 1;

	UPROPERTY(ReplicatedUsing=OnRep_UpdateHUD)
	float RaceTime = 0.f;

	UFUNCTION()
	void OnRep_UpdateHUD();

	UPROPERTY()
	URaceHUDWidget* RaceHUD;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY()
	TMap<APlayerController*, URaceHUDWidget*> PlayerHUDs;

private:
	UPROPERTY()
	APlayerController* CachedPC;
	
	void UpdateRaceTime();
}; 