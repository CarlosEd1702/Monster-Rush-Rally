// Copyright Epic Games, Inc. All Rights Reserved.

#include "MonsterRushRallyGameMode.h"
#include "MonsterRushRallyPlayerController.h"

AMonsterRushRallyGameMode::AMonsterRushRallyGameMode()
{
	PlayerControllerClass = AMonsterRushRallyPlayerController::StaticClass();
}
