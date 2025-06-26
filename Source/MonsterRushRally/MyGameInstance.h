// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERRUSHRALLY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Game State")
	int32 NumPlayers;

	UPROPERTY(BlueprintReadWrite, Category = "Game State")
	TSubclassOf<AGameModeBase> SelectedGameMode;
};
