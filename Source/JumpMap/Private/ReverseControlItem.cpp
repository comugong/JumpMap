#include "ReverseControlItem.h"
#include "NewCharacter.h"

AReverseControlItem::AReverseControlItem() {
	ReverseDuration = 5.0f;
	ItemType = "Reverse";
}

void AReverseControlItem::ActivateItem(AActor* Activator) {
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player")) {
		if (ANewCharacter* PlayerCharacter = Cast<ANewCharacter>(Activator)) {
			PlayerCharacter->ReverseControl(ReverseDuration);
		}
		DestroyItem();
	}
}