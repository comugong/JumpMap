#include "NewGameMode.h"
#include "NewCharacter.h"
#include "NewPlayerController.h"
#include "NewGameState.h"

ANewGameMode::ANewGameMode() {
	DefaultPawnClass = ANewCharacter::StaticClass();
	PlayerControllerClass = ANewPlayerController::StaticClass();
	GameStateClass = ANewGameState::StaticClass();
}