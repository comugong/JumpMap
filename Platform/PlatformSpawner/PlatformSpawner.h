#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

UCLASS()
class JUMPMAP_API APlatformSpawner : public AActor {
    GENERATED_BODY()

public:
    APlatformSpawner();

protected:
    virtual void BeginPlay() override;
};
