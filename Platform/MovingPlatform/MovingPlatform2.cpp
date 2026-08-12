#include "MovingPlatform2.h"

AMovingPlatform2::AMovingPlatform2() {
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = false;
}

void AMovingPlatform2::BeginPlay() {
	Super::BeginPlay();
	
	MoveSpeed = FMath::RandRange(0.0f, 500.0f);
	Count = 0;

	MoveDirection[0] = FVector(0.0f, MoveSpeed, 0.0f);
	MoveDirection[1] = FVector(MoveSpeed, 0.0f, 0.0f);
	MoveDirection[2] = FVector(0.0f, -MoveSpeed, 0.0f);
	MoveDirection[3] = FVector(-MoveSpeed, 0.0f, 0.0f);

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&AMovingPlatform2::MoveLikeSquare,
		5.0f,
		true
	);
}

void AMovingPlatform2::MoveLikeSquare() {
	if (!FMath::IsNearlyZero(MoveSpeed)) {
		AddActorWorldOffset(MoveDirection[Count]);
	}

	++Count;
	if (Count >= sizeof(MoveDirection) / sizeof(MoveDirection[0])) {
		Count = 0;
	}
}
