// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayModeComponent.generated.h"

class UUserWidget;

UCLASS(Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERRUSHRALLY_API UGameplayModeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameplayModeComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	UUserWidget* HUDWidget;
		
};
