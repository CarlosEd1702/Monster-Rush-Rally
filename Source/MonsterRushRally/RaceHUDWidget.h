// RaceHUDWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RaceHUDWidget.generated.h"

class UTextBlock;

UCLASS()
class MONSTERRUSHRALLY_API URaceHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateRaceHUD(float RaceTime, int32 CurrentLap, int32 TotalLaps,
		int32 CurrentCheckpoint, int32 TotalCheckpoints, int32 Position);

	UFUNCTION(BlueprintImplementableEvent)
	void SetRaceFinished();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_RaceTime;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CurrentLap;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_TotalLaps;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CurrentCheckpoint;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_TotalCheckpoints;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Position;
};
