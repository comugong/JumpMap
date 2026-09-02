#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "BlindItem.generated.h"

UCLASS()
class JUMPMAP_API ABlindItem : public ABaseItem {
	GENERATED_BODY()
	
public:
	ABlindItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float BlindIntensity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float BlindDuration;

	virtual void ActivateItem(AActor* Activator) override;
};