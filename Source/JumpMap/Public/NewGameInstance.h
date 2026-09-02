#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NewGameInstance.generated.h"

UCLASS()
class JUMPMAP_API UNewGameInstance : public UGameInstance {
	GENERATED_BODY()

public:
	UNewGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentLevelIndex;
	
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);
};
