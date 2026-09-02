#include "Spike.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ASpike::ASpike() {
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(Scene);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASpike::OnSpikeOverlap);

	SpikeDamage = 30;
	RiseHeight = 100.0f;
	RiseDuration = 0.4f;
	FallDuration = 0.6f;
	WaitDuration = 1.5f;
	ElapsedTime = 0.0f;
	SpikeState = ESpikeState::Waiting;
}

void ASpike::OnSpikeOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult) {

	if (OtherActor && OtherActor->ActorHasTag("Player")) {
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.0f,
			FColor::Green,
			TEXT("Spike Overlap")
		);

		ActivateItem(OtherActor);
	}
}

void ASpike::ActivateItem(AActor* Activator) {
	if (!Activator) {
		return;
	}

	UGameplayStatics::ApplyDamage(
		Activator,
		SpikeDamage,
		nullptr,
		this,
		UDamageType::StaticClass()
	);
}

void ASpike::BeginPlay() {
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	EndLocation = StartLocation + FVector(0.0f, 0.0f, RiseHeight);
}

void ASpike::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;
	float Alpha = 0.0f;

	switch (SpikeState) {
	case ESpikeState::Waiting:
		if (ElapsedTime >= WaitDuration) {
			ElapsedTime = 0.0f;
			SpikeState = ESpikeState::Rising;
		}
		break;

	case ESpikeState::Rising:
		Alpha = FMath::Clamp(ElapsedTime / RiseDuration, 0.0f, 1.0f);
		SetActorLocation(FMath::Lerp(StartLocation, EndLocation, Alpha));

		if (Alpha >= 1.0f) {
			ElapsedTime = 0.0f;
			SpikeState = ESpikeState::Falling;
		}
		break;

	case ESpikeState::Falling:
		Alpha = FMath::Clamp(ElapsedTime / FallDuration, 0.0f, 1.0f);
		SetActorLocation(FMath::Lerp(EndLocation, StartLocation, Alpha));

		if (Alpha >= 1.0f) {
			ElapsedTime = 0.0f;
			SpikeState = ESpikeState::Waiting;
		}
		break;
	}
}