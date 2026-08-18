#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NewPawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class JUMPMAP_API ANewPawn : public APawn {
	GENERATED_BODY()

public:
	ANewPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* SkeletalMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void VerticalMove(const FInputActionValue& value);
	UFUNCTION()
	void Roll(const FInputActionValue& value);

private:
	float VerticalVelocity;
	float Gravity;
	bool bIsGrounded;
};