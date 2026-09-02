#include "ExplosionSpawnVolume.h"
#include "Components/BoxComponent.h"

AExplosionSpawnVolume::AExplosionSpawnVolume() {
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	ExplosionClass = nullptr;
	ExplosionDelay = 15.0f;
	ExplosionQuantity = 10;
}

void AExplosionSpawnVolume::SpawnExplosion() {
	if (!ExplosionClass || !SpawningBox) {
		return;
	}

	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();
	FVector SpawnLocation(FMath::FRandRange(BoxOrigin.X - BoxExtent.X, BoxOrigin.X + BoxExtent.X), FMath::FRandRange(BoxOrigin.Y - BoxExtent.Y, BoxOrigin.Y + BoxExtent.Y), BoxOrigin.Z);

	GetWorld()->SpawnActor<AActor>(
		ExplosionClass,
		SpawnLocation,
		FRotator::ZeroRotator
	);
}

void AExplosionSpawnVolume::LoopSpawnExplosion() {
	GetWorldTimerManager().SetTimer(
		ExplosionTimerHandle,
		this,
		&AExplosionSpawnVolume::SpawnExplosionBatch,
		ExplosionDelay,
		true
	);
}

void AExplosionSpawnVolume::SpawnExplosionBatch() {
	for (int32 i = 0; i < ExplosionQuantity; ++i) {
		SpawnExplosion();
	}
	UE_LOG(LogTemp, Warning, TEXT("Explosion %d만큼 생성"), ExplosionQuantity);
}