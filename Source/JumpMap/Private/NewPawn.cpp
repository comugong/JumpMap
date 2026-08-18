#include "NewPawn.h"
#include "NewPawnController.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ANewPawn::ANewPawn() {
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = CapsuleComp;
	CapsuleComp->InitCapsuleSize(42.0f, 96.0f);
	CapsuleComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(RootComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	PrimaryActorTick.bCanEverTick = true;
	VerticalVelocity = 0.0f;
	Gravity = -980.0f;
	bIsGrounded = false;
}

void ANewPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		if (ANewPawnController* PawnController = Cast<ANewPawnController>(GetController())) {
			if (PawnController->MoveAction) {
				EnhancedInput->BindAction(
					PawnController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ANewPawn::Move
				);
			}

			if (PawnController->LookAction) {
				EnhancedInput->BindAction(
					PawnController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ANewPawn::Look
				);
			}

			if (PawnController->VerticalMoveAction) {
				EnhancedInput->BindAction(
					PawnController->VerticalMoveAction,
					ETriggerEvent::Triggered,
					this,
					&ANewPawn::VerticalMove
				);
			}

			if (PawnController->RollAction) {
				EnhancedInput->BindAction(
					PawnController->RollAction,
					ETriggerEvent::Triggered,
					this,
					&ANewPawn::Roll
				);
			}
		}
	}
}

void ANewPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!bIsGrounded) {
		VerticalVelocity += Gravity * DeltaTime;
	}
	const FVector StartLocation = GetActorLocation();
	FVector Movement(0.0f, 0.0f, VerticalVelocity * DeltaTime);
	const FVector EndLocation = StartLocation + Movement;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	const bool bHit = GetWorld()->SweepSingleByChannel(
		Hit,
		StartLocation,
		EndLocation,
		GetActorQuat(),
		ECC_Visibility,
		CapsuleComp->GetCollisionShape(),
		Params
	);

	if (bHit && Hit.Normal.Z > 0.7f) {
		AddActorWorldOffset(Movement * Hit.Time);
		VerticalVelocity = 0.0f;
		bIsGrounded = true;
	}
	else {
		AddActorWorldOffset(Movement, true);
		bIsGrounded = false;
	}
}

void ANewPawn::Move(const FInputActionValue& value) {
	const FVector2D MoveVector = value.Get<FVector2D>();
	const float DeltaTime = GetWorld()->GetDeltaSeconds();

	const float GroundSpeed = 1200.0f;
	const float AirControlMultiplier = 0.4f;
	const float AirSpeed = GroundSpeed * AirControlMultiplier;

	const float Speed = bIsGrounded ? GroundSpeed : AirSpeed;

	const FVector Forward = GetActorForwardVector();
	const FVector Right = GetActorRightVector();

	FVector Movement = Forward * MoveVector.X + Right * MoveVector.Y;
	if (!Movement.IsNearlyZero()) {
		Movement.Normalize();
		Movement *= Speed * DeltaTime;
		AddActorWorldOffset(Movement, true);
	}
}

void ANewPawn::Look(const FInputActionValue& value) {
	const FVector2D LookVector = value.Get<FVector2D>();
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	const float LookSpeed = 100.0f;

	const float Yaw = LookVector.X * LookSpeed * DeltaTime;
	const float Pitch = LookVector.Y * LookSpeed * DeltaTime;

	AddActorLocalRotation(FRotator(Pitch, Yaw, 0.0f));
}

void ANewPawn::VerticalMove(const FInputActionValue& value) {
	const float Input = value.Get<float>();
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	const float Speed = 1200.0f;
	
	const FVector Up = GetActorUpVector();
	const FVector Movement = Up * Input * Speed * DeltaTime;
	AddActorWorldOffset(Movement, true);

	VerticalVelocity = 0.0f;
}

void ANewPawn::Roll(const FInputActionValue& value) {
	const float Input = value.Get<float>();
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	const float RollSpeed = 100.0f;

	const float RollAmount = Input * RollSpeed * DeltaTime;
	AddActorLocalRotation(FRotator(0.0f, 0.0f, RollAmount));
}