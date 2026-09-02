#include "SpikeSpawnVolume.h"
#include "Components/BoxComponent.h"

ASpikeSpawnVolume::ASpikeSpawnVolume() {
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	SpikeClass = nullptr;
	SpikeInterval = 200.0f;
}

void ASpikeSpawnVolume::SpawnSpike() {
	if (!SpikeClass || !SpawningBox) {
		return;
	}

	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	float StartX = BoxOrigin.X - BoxExtent.X;
	float EndX = BoxOrigin.X + BoxExtent.X;
	float StartY = BoxOrigin.Y - BoxExtent.Y;
	float EndY = BoxOrigin.Y + BoxExtent.Y;
	float Z = BoxOrigin.Z;

	for (float X = StartX; X <= EndX; X += SpikeInterval) {
		for (float Y = StartY; Y <= EndY; Y += SpikeInterval) {
			FVector SpawnLocation(X, Y, Z);

			GetWorld()->SpawnActor<AActor>(
				SpikeClass,
				SpawnLocation,
				FRotator::ZeroRotator
			);
		}
	}
}