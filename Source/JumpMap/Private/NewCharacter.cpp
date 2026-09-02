#include "NewCharacter.h"
#include "NewPlayerController.h"
#include "NewGameState.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"

ANewCharacter::ANewCharacter() {
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(GetMesh());
	OverheadWidget->SetWidgetSpace(EWidgetSpace::Screen);

	PrimaryActorTick.bCanEverTick = false;
	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.5f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	MaxHealth = 100.0f;
	Health = MaxHealth;

	bIsSlowed = false;
	OriginNormalSpeed = NormalSpeed;

	bIsReversed = false;

	bIsBlinded = false;
}

void ANewCharacter::BeginPlay() {
	Super::BeginPlay();
	UpdateOverheadHP();
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

	if (bIsReversed) {
		MoveInput *= -1.0f;
	}

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

float ANewCharacter::GetHealth() const {
	return Health;
}

void ANewCharacter::AddHealth(float amount) {
	Health = FMath::Clamp(Health + amount, 0.0f, MaxHealth);
	UpdateOverheadHP();
}

float ANewCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);
	UpdateOverheadHP();

	if (Health <= 0.0f) {
		OnDeath();
	}

	return ActualDamage;
}

void ANewCharacter::OnDeath() {
	ANewGameState* NewGameState = GetWorld() ? GetWorld()->GetGameState<ANewGameState>() : nullptr;
	if (NewGameState) {
		NewGameState->OnGameOver();
	}
}

void ANewCharacter::UpdateOverheadHP() {
	if (!OverheadWidget) return;

	UUserWidget* OverheadWidgetInstance = OverheadWidget->GetUserWidgetObject();
	if (!OverheadWidgetInstance) return;

	if (UTextBlock* HPText = Cast<UTextBlock>(OverheadWidgetInstance->GetWidgetFromName(TEXT("OverHeadHp")))) {
		HPText->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), Health, MaxHealth)));
	}
}

void ANewCharacter::Slow(float SlowValue, float SlowDuration) {
	if (!bIsSlowed) {
		OriginNormalSpeed = NormalSpeed;
		NormalSpeed *= SlowValue;
		SprintSpeed = NormalSpeed * SprintSpeedMultiplier;
		bIsSlowed = true;
	}

	GetWorldTimerManager().SetTimer(
		SlowTimerHandle,
		this,
		&ANewCharacter::EndSlow,
		SlowDuration,
		false
	);
}

void ANewCharacter::EndSlow() {
	NormalSpeed = OriginNormalSpeed;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;
	bIsSlowed = false;
}

bool ANewCharacter::IsSlowed() const {
	return bIsSlowed;
}

float ANewCharacter::GetRemainingSlowTime() const {
	return GetWorldTimerManager().GetTimerRemaining(SlowTimerHandle);
}

void ANewCharacter::ReverseControl(float ReverseDuration) {
	bIsReversed = true;

	GetWorldTimerManager().SetTimer(
		ReverseTimerHandle,
		this,
		&ANewCharacter::EndReverseControl,
		ReverseDuration,
		false
	);
}

void ANewCharacter::EndReverseControl() {
	bIsReversed = false;
}

bool ANewCharacter::IsReversed() const {
	return bIsReversed;
}

float ANewCharacter::GetRemainingReverseTime() const {
	return GetWorldTimerManager().GetTimerRemaining(ReverseTimerHandle);
}

void ANewCharacter::Blind(float BlindIntensity, float BlindDuration) {
	bIsBlinded = true;
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		if (ANewPlayerController* NewPlayerController = Cast<ANewPlayerController>(PlayerController)) {
			NewPlayerController->ShowBlind(bIsBlinded, BlindIntensity);
		}
	}

	GetWorldTimerManager().SetTimer(
		BlindTimerHandle,
		this,
		&ANewCharacter::EndBlind,
		BlindDuration,
		false
	);
}

void ANewCharacter::EndBlind() {
	bIsBlinded = false;
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		if (ANewPlayerController* NewPlayerController = Cast<ANewPlayerController>(PlayerController)) {
			NewPlayerController->ShowBlind(bIsBlinded, 0.0f);
		}
	}
}

bool ANewCharacter::IsBlinded() const {
	return bIsBlinded;
}

float ANewCharacter::GetRemainingBlindTime() const {
	return GetWorldTimerManager().GetTimerRemaining(BlindTimerHandle);
}