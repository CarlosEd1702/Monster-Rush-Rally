// Copyright Epic Games, Inc. All Rights Reserved.


#include "MonsterRushRallyPlayerController.h"
#include "MonsterRushRallyPawn.h"
#include "MonsterRushRallyUI.h"
#include "EnhancedInputSubsystems.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "RaceComponent.h"
#include "GameFramework/GameModeBase.h"

void AMonsterRushRallyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (AGameModeBase* GM = GetWorld()->GetAuthGameMode())
	{
		if (IGameplayModeInterface* Mode = Cast<IGameplayModeInterface>(GM))
		{
			Mode->InitPlayerComponent(this); // Llama a la lógica del GameMode correcto
		}
	}
}

void AMonsterRushRallyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		// optionally add the steering wheel context
		if (bUseSteeringWheelControls && SteeringWheelInputMappingContext)
		{
			Subsystem->AddMappingContext(SteeringWheelInputMappingContext, 1);
		}
	}
}

void AMonsterRushRallyPlayerController::Tick(float Delta)
{
	Super::Tick(Delta);

	if (IsValid(VehiclePawn) && IsValid(VehicleUI))
	{
		VehicleUI->UpdateSpeed(VehiclePawn->GetChaosVehicleMovement()->GetForwardSpeed());
		VehicleUI->UpdateGear(VehiclePawn->GetChaosVehicleMovement()->GetCurrentGear());
	}
}

void AMonsterRushRallyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// get a pointer to the controlled pawn
	VehiclePawn = CastChecked<AMonsterRushRallyPawn>(InPawn);
}
