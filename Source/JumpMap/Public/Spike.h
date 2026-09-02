#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spike.generated.h"

class UBoxComponent;
enum class ESpikeState {
	Waiting,
	Rising,
	Falling
};

UCLASS()
class JUMPMAP_API ASpike : public AActor {
	GENERATED_BODY()
	
public:	
	ASpike();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spike")
	UBoxComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spike")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spike")
	int32 SpikeDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spike")
	float RiseHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spike")
	float RiseDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spike")
	float FallDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spike")
	float WaitDuration;

	UFUNCTION()
	void OnSpikeOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void ActivateItem(AActor* Activator);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	FVector StartLocation;
	FVector EndLocation;
	float ElapsedTime;

	ESpikeState SpikeState;
};
