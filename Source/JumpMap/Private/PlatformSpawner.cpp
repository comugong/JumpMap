#include "PlatformSpawner.h"
#include "RotatingPlatform1.h"
#include "MovingPlatform1.h"

APlatformSpawner::APlatformSpawner() {
	PrimaryActorTick.bCanEverTick = false;
}

void APlatformSpawner::BeginPlay() {
	Super::BeginPlay();

    PlatformSpawn();
}

void APlatformSpawner::PlatformSpawn() {
    for (int32 i = 0; i < 10; ++i) {
        FVector Location(FMath::RandRange(-2000.0f, 2000.0f), FMath::RandRange(-2000.0f, 2000.0f), 100.0f);
        FRotator Rotation = FRotator::ZeroRotator;

        if (FMath::RandRange(0, 1) == 0) {
            GetWorld()->SpawnActor<ARotatingPlatform1>(ARotatingPlatform1::StaticClass(), Location, Rotation);
        }
        else {
            GetWorld()->SpawnActor<AMovingPlatform1>(AMovingPlatform1::StaticClass(), Location, Rotation);
        }
    }
}