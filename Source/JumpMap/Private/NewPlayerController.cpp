#include "NewPlayerController.h"
#include "NewGameState.h"
#include "NewGameInstance.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

ANewPlayerController::ANewPlayerController()
	: InputMappingContext(nullptr),
	  MoveAction(nullptr),
	  JumpAction(nullptr),
	  LookAction(nullptr),
	  SprintAction(nullptr),
	  HUDWidgetClass(nullptr),
	  HUDWidgetInstance(nullptr),
	  MainMenuWidgetClass(nullptr),
	  MainMenuWidgetInstance(nullptr),
	  BlindWidgetClass(nullptr),
	  BlindWidgetInstance(nullptr)
{
}

void ANewPlayerController::BeginPlay() {
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer()) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) {
			if (InputMappingContext) {
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel")) {
		ShowMainMenu(false);
	}
}

UUserWidget* ANewPlayerController::GetHUDWidget() const {
	return HUDWidgetInstance;
}

void ANewPlayerController::ShowMainMenu(bool bIsRestart) {
	if (HUDWidgetInstance) {
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance) {
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (MainMenuWidgetClass) {
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance) {
			MainMenuWidgetInstance->AddToViewport();
			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}

		if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText")))) {
			if (bIsRestart) {
				ButtonText->SetText(FText::FromString(TEXT("Restart")));
			}
			else {
				ButtonText->SetText(FText::FromString(TEXT("Start")));
			}
		}

		if (bIsRestart) {
			UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
			if (PlayAnimFunc) {
				MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
			}

			if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName("TotalScoreText"))) {
				if (UNewGameInstance* NewGameInstance = Cast<UNewGameInstance>(UGameplayStatics::GetGameInstance(this))) {
					TotalScoreText->SetText(FText::FromString(FString::Printf(TEXT("Total Score %d"), NewGameInstance->TotalScore)));
				}
			}
		}
	}
}

void ANewPlayerController::ShowGameHUD() {
	if (HUDWidgetInstance) {
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance) {
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (HUDWidgetClass) {
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance) {
			HUDWidgetInstance->AddToViewport();
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
		}

		ANewGameState* NewGameState = GetWorld() ? GetWorld()->GetGameState<ANewGameState>() : nullptr;
		if (NewGameState) {
			NewGameState->UpdateHUD();
		}
	}
}

void ANewPlayerController::StartGame() {
	if (UNewGameInstance* NewGameInstance = Cast<UNewGameInstance>(UGameplayStatics::GetGameInstance(this))) {
		NewGameInstance->CurrentLevelIndex = 0;
		NewGameInstance->TotalScore = 0;
	}

	UGameplayStatics::OpenLevel(GetWorld(), FName("BasicLevel"));
	SetPause(false);
}

void ANewPlayerController::ShowBlind(bool bIsBlinded, float BlindIntensity) {
	if (bIsBlinded) {
		if (!BlindWidgetInstance && BlindWidgetClass) {
			BlindWidgetInstance = CreateWidget<UUserWidget>(this, BlindWidgetClass);
			if (BlindWidgetInstance) {
				BlindWidgetInstance->AddToViewport();
			}
		}

		if (BlindWidgetInstance) {
			if (UFunction* BlindFunc = BlindWidgetInstance->FindFunction(FName("VisibleBlind"))) {
				BlindWidgetInstance->ProcessEvent(BlindFunc, nullptr);
			}

			if (UImage* BlindImage = Cast<UImage>(BlindWidgetInstance->GetWidgetFromName(TEXT("BlindImage")))) {
				BlindImage->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, BlindIntensity));
			}
		}
	}
	else {
		if (BlindWidgetInstance) {
			if (UFunction* BlindFunc = BlindWidgetInstance->FindFunction(FName("HiddenBlind"))) {
				BlindWidgetInstance->ProcessEvent(BlindFunc, nullptr);
			}

			BlindWidgetInstance->RemoveFromParent();
			BlindWidgetInstance = nullptr;
		}
	}
}