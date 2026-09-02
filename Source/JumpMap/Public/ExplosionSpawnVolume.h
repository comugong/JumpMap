#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosionSpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class JUMPMAP_API AExplosionSpawnVolume : public AActor {
	GENERATED_BODY()

public:
	AExplosionSpawnVolume();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<AActor> ExplosionClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	float ExplosionDelay;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	int32 ExplosionQuantity;

	void SpawnExplosion();
	void SpawnExplosionBatch();

	FTimerHandle ExplosionTimerHandle;

public:
	UFUNCTION(BlueprintCallable, Category = "Explosion")
	void LoopSpawnExplosion();
};