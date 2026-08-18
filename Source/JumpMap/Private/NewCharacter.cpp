#include "NewCharacter.h"
#include "NewPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ANewCharacter::ANewCharacter() {
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	PrimaryActorTick.bCanEverTick = false;
	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.5f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}

void ANewCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		if (ANewPlayerController* PlayerController = Cast<ANewPlayerController>(GetController())) {
			if (PlayerController->MoveAction) {
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ANewCharacter::Move
				);
			}

			if (PlayerController->JumpAction) {
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&ANewCharacter::StartJump
				);

				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&ANewCharacter::StopJump
				);
			}

			if (PlayerController->LookAction) {
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ANewCharacter::Look
				);
			}

			if (PlayerController->SprintAction) {
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&ANewCharacter::StartSprint
				);

				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&ANewCharacter::StopSprint
				);
			}
		}
	}
}

void ANewCharacter::Move(const FInputActionValue& value) {
	if (!Controller) return;

	FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X)) {
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y)) {
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void ANewCharacter::StartJump(const FInputActionValue& value) {
	if (value.Get<bool>()) {
		Jump();
	}
}

void ANewCharacter::StopJump(const FInputActionValue& value) {
	if (!value.Get<bool>()) {
		StopJumping();
	}
}

void ANewCharacter::Look(const FInputActionValue& value) {
	const FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void ANewCharacter::StartSprint(const FInputActionValue& value) {
	if (GetCharacterMovement()) {
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void ANewCharacter::StopSprint(const FInputActionValue& value) {
	if (GetCharacterMovement()) {
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}
