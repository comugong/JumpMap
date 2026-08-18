#include "NewGameMode.h"
#include "NewPawn.h"
#include "NewPawnController.h"

ANewGameMode::ANewGameMode() {
	DefaultPawnClass = ANewPawn::StaticClass();
	PlayerControllerClass = ANewPawnController::StaticClass();
}