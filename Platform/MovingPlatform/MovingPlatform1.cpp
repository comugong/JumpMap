#include "MovingPlatform1.h"

AMovingPlatform1::AMovingPlatform1() {
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Sphere.SM_Sphere"));

	if (MeshAsset.Succeeded()) {
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	PrimaryActorTick.bCanEverTick = true;
	MoveSpeed = 100.0f;
	MaxRange = 500.0f;
	MoveDirection = 1.0f;
}

void AMovingPlatform1::BeginPlay() {
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
}

void AMovingPlatform1::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// 두 지점 사이의 거리 (Y축)
	float StartY = StartLocation.Y;
	float CurrentY = GetActorLocation().Y;

	if (CurrentY >= StartY + MaxRange && MoveDirection > 0) {
		MoveDirection = -1.0f;
	}
	else if (CurrentY <= StartY - MaxRange && MoveDirection < 0) {
		MoveDirection = 1.0f;
	}

	if (!FMath::IsNearlyZero(MoveSpeed)) {
		AddActorWorldOffset(FVector(0.0f, MoveSpeed * MoveDirection * DeltaTime, 0.0f));
	}
}
