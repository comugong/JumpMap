#include "RotatingPlatform2.h"

ARotatingPlatform2::ARotatingPlatform2() {
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
}

void ARotatingPlatform2::BeginPlay() {
	Super::BeginPlay();
	
	RotationSpeed = FMath::RandRange(0.0f, 500.0f);

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&ARotatingPlatform2::ToggleAppearPlatform,
		5.0f,
		true
	);
}

void ARotatingPlatform2::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed)) {
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}
}

void ARotatingPlatform2::ToggleAppearPlatform() {
	SetActorHiddenInGame(!IsHidden);
	SetActorEnableCollision(IsHidden);

	if (IsHidden) {
		IsHidden = false;
	}
	else {
		IsHidden = true;
	}
}