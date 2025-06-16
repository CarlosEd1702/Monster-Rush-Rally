// Copyright Epic Games, Inc. All Rights Reserved.

#include "MonsterRushRallyWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UMonsterRushRallyWheelRear::UMonsterRushRallyWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}