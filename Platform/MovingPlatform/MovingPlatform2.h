#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform2.generated.h"

UCLASS()
class JUMPMAP_API AMovingPlatform2 : public AActor {
	GENERATED_BODY()
	
public:	
	AMovingPlatform2();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Components")
	UStaticMeshComponent* StaticMeshComp;

	// 이동 속도
	float MoveSpeed;

	// 이동 방향
	FVector MoveDirection[4];

	// 이동 방향 인덱스
	int Count;

	// 타이머
	FTimerHandle TimerHandle;

	virtual void BeginPlay() override;
	void MoveLikeSquare();
};
