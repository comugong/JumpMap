#include "RotatingPlatform1.h"

ARotatingPlatform1::ARotatingPlatform1() {
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Coin_A.SM_Coin_A"));

	if (MeshAsset.Succeeded()) {
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.0f;
}

void ARotatingPlatform1::BeginPlay() {
	Super::BeginPlay();
}

void ARotatingPlatform1::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed)) {
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}
}