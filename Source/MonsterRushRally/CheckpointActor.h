#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointActor.generated.h"

class UBoxComponent;

UCLASS()
class MONSTERRUSHRALLY_API ACheckpointActor : public AActor
{
	GENERATED_BODY()
	
public:
	ACheckpointActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Checkpoint")
	UBoxComponent* TriggerBox;

	// Index del checkpoint en la pista (puede ser útil si decides ordenarlos)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Checkpoint")
	int32 CheckpointIndex = 0;

	// Si es la línea de meta
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Checkpoint")
	bool bIsFinishLine = false;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

	void NotifyGameMode(APlayerController* PC);
};
