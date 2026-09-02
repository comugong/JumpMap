#include "HealingItem.h"
#include "NewCharacter.h"

AHealingItem::AHealingItem() {
	HealAmount = 20.0f;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator) {
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player")) {
		if (ANewCharacter* PlayerCharacter = Cast<ANewCharacter>(Activator)) {
			PlayerCharacter->AddHealth(HealAmount);
		}
		DestroyItem();
	}
}