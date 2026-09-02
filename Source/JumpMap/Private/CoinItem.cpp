#include "CoinItem.h"
#include "Engine/World.h"
#include "NewGameState.h"

ACoinItem::ACoinItem() {
	PointValue = 0;
	ItemType = "DefaultCoin";
}

void ACoinItem::ActivateItem(AActor* Activator) {
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player")) {
		if (UWorld* World = GetWorld()) {
			if (ANewGameState* GameState = World->GetGameState<ANewGameState>()) {
				GameState->AddScore(PointValue);
				GameState->OnCoinCollected();
			}
		}
		DestroyItem();
	}
}