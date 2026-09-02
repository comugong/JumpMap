#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "SlowingItem.generated.h"

UCLASS()
class JUMPMAP_API ASlowingItem : public ABaseItem {
	GENERATED_BODY()

public:
	ASlowingItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float SlowValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float SlowDuration;

	virtual void ActivateItem(AActor* Activator) override;
};