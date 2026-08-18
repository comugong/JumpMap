#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NewPawnController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class JUMPMAP_API ANewPawnController : public APlayerController {
	GENERATED_BODY()
	
public:
	ANewPawnController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* VerticalMoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* RollAction;

protected:
	virtual void BeginPlay() override;
};
