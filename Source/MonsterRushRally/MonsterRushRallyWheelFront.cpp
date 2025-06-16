// Copyright Epic Games, Inc. All Rights Reserved.

#include "MonsterRushRallyWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UMonsterRushRallyWheelFront::UMonsterRushRallyWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}