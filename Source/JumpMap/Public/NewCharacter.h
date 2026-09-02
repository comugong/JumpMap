#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NewCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
struct FInputActionValue;

UCLASS()
class JUMPMAP_API ANewCharacter : public ACharacter {
	GENERATED_BODY()

public:
	ANewCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* OverheadWidget;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Debuff|Speed")
	void Slow(float SlowValue, float SlowDuration);
	UFUNCTION(BlueprintCallable, Category = "Debuff|Speed")
	void EndSlow();
	UFUNCTION(BlueprintPure, Category = "Debuff|Speed")
	bool IsSlowed() const;
	UFUNCTION(BlueprintPure, Category = "Debuff|Speed")
	float GetRemainingSlowTime() const;

	UFUNCTION(BlueprintCallable, Category = "Debuff|Reverse")
	void ReverseControl(float ReverseDuration);
	UFUNCTION(BlueprintCallable, Category = "Debuff|Reverse")
	void EndReverseControl();
	UFUNCTION(BlueprintPure, Category = "Debuff|Reverse")
	bool IsReversed() const;
	UFUNCTION(BlueprintPure, Category = "Debuff|Reverse")
	float GetRemainingReverseTime() const;

	UFUNCTION(BlueprintCallable, Category = "Debuff|Blind")
	void Blind(float BlindIntensity, float BlindDuration);
	UFUNCTION(BlueprintCallable, Category = "Debuff|Blind")
	void EndBlind();
	UFUNCTION(BlueprintPure, Category = "Debuff|Blind")
	bool IsBlinded() const;
	UFUNCTION(BlueprintPure, Category = "Debuff|Blind")
	float GetRemainingBlindTime() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);

	void OnDeath();
	void UpdateOverheadHP();

private:
	float NormalSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;
	float OriginNormalSpeed;

	bool bIsSlowed;
	FTimerHandle SlowTimerHandle;

	bool bIsReversed;
	FTimerHandle ReverseTimerHandle;

	bool bIsBlinded;
	FTimerHandle BlindTimerHandle;
};