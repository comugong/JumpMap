#include "SlowingItem.h"
#include "NewCharacter.h"

ASlowingItem::ASlowingItem() {
	SlowValue = 0.5f;
	SlowDuration = 5.0f;
	ItemType = "Slowing";
}

void ASlowingItem::ActivateItem(AActor* Activator) {
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player")) {
		if (ANewCharacter* PlayerCharacter = Cast<ANewCharacter>(Activator)) {
			PlayerCharacter->Slow(SlowValue, SlowDuration);
		}
		DestroyItem();
	}
}