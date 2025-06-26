#include "CheckpointActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode_ClassicRace.h"

ACheckpointActor::ACheckpointActor()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->SetCollisionProfileName("Trigger");
}

void ACheckpointActor::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerBox)
	{
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointActor::OnOverlapBegin);
	}
}

void ACheckpointActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
									  bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (!Pawn) return;

	APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
	if (!PC) return;

	NotifyGameMode(PC);
}

void ACheckpointActor::NotifyGameMode(APlayerController* PC)
{
	AGameMode_ClassicRace* GM = Cast<AGameMode_ClassicRace>(UGameplayStatics::GetGameMode(this));
	if (!GM) return;

	// Llama al GameMode para manejar el progreso
	int32 NextLap = bIsFinishLine ? 1 : 0; // solo se incrementará si es finish line
	GM->OnPlayerCheckpoint(PC, NextLap);
}
