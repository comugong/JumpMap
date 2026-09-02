#include "BlindItem.h"
#include "NewCharacter.h"

ABlindItem::ABlindItem() {
	BlindIntensity = 0.5f;
	BlindDuration = 5.0f;
	ItemType = "Blind";
}

void ABlindItem::ActivateItem(AActor* Activator) {
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player")) {
		if (ANewCharacter* PlayerCharacter = Cast<ANewCharacter>(Activator)) {
			PlayerCharacter->Blind(BlindIntensity, BlindDuration);
		}
		DestroyItem();
	}
}