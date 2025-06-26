#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayModeInterface.generated.h"

UINTERFACE(MinimalAPI)
class UGameplayModeInterface : public UInterface
{
	GENERATED_BODY()
};

class MONSTERRUSHRALLY_API IGameplayModeInterface
{
	GENERATED_BODY()

public:
	virtual void OnRaceProgress(APlayerController* PC, float NewTime, int32 NewLap, int32 Position) = 0;

	virtual void InitPlayerComponent(APlayerController* PC) = 0;
};
