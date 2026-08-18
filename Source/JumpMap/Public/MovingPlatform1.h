#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform1.generated.h"

UCLASS()
class JUMPMAP_API AMovingPlatform1 : public AActor {
	GENERATED_BODY()
	
public:	
	AMovingPlatform1();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Components")
	UStaticMeshComponent* StaticMeshComp;

	// 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform|Properties")
	float MoveSpeed;

	// 최대 이동 거리
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform|Properties")
	float MaxRange;

	// 출발점
	FVector StartLocation;

	// 이동 방향
	float MoveDirection;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};