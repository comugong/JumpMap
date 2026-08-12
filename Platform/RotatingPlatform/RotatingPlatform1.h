#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingPlatform1.generated.h"

UCLASS()
class JUMPMAP_API ARotatingPlatform1 : public AActor {
	GENERATED_BODY()

public:
	ARotatingPlatform1();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Components")
	UStaticMeshComponent* StaticMeshComp;

	// 회전 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform|Properties")
	float RotationSpeed;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
