// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayModeComponent.h"

// Sets default values for this component's properties
UGameplayModeComponent::UGameplayModeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGameplayModeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
