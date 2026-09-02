#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpikeSpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class JUMPMAP_API ASpikeSpawnVolume : public AActor {
	GENERATED_BODY()

public:
	ASpikeSpawnVolume();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<AActor> SpikeClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	float SpikeInterval;

public:
	void SpawnSpike();
};