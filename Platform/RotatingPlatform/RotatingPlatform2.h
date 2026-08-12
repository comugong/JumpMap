#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingPlatform2.generated.h"

UCLASS()
class JUMPMAP_API ARotatingPlatform2 : public AActor {
	GENERATED_BODY()
	
public:	
	ARotatingPlatform2();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Components")
	UStaticMeshComponent* StaticMeshComp;

	// 회전 속도
	float RotationSpeed;

	// 타이머
	FTimerHandle TimerHandle;

	// 플랫폼 토글 여부
	bool IsHidden = false;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void ToggleAppearPlatform();
};
