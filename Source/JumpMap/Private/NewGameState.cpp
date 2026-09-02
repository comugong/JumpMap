#include "NewGameState.h"
#include "NewGameInstance.h"
#include "NewCharacter.h"
#include "NewPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "SpikeSpawnVolume.h"
#include "ExplosionSpawnVolume.h"
#include "CoinItem.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

ANewGameState::ANewGameState() {
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	WaveDuration = {60.0f, 45.0f, 30.0f};
	ItemToSpawn = { 60, 45, 30 };
	CurrentLevelIndex = 0;
	CurrentWaveIndex = 0;
	MaxLevel = 3;
	MaxWave = 3;
}

void ANewGameState::BeginPlay() {
	Super::BeginPlay();

	FString CurrentMapName = GetWorld()->GetMapName();
	if (!CurrentMapName.Contains("MenuLevel")) {
		StartLevel();

		GetWorldTimerManager().SetTimer(
			HUDUpdateTimerHandle,
			this,
			&ANewGameState::UpdateHUD,
			0.1f,
			true
		);
	}
}

int32 ANewGameState::GetScore() const {
	if (const UNewGameInstance* NewGameInstance = Cast<UNewGameInstance>(GetGameInstance())) {
		return NewGameInstance->TotalScore;
	}

	return 0;
}

void ANewGameState::AddScore(int32 Amount) {
	if (UGameInstance* GameInstance = GetGameInstance()) {
		UNewGameInstance* NewGameInstance = Cast<UNewGameInstance>(GameInstance);
		if (NewGameInstance) {
			NewGameInstance->AddToScore(Amount);
		}
	}
}

void ANewGameState::StartLevel() {
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		if (ANewPlayerController* NewPlayerController = Cast<ANewPlayerController>(PlayerController)) {
			NewPlayerController->ShowGameHUD();
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance()) {
		UNewGameInstance* NewGameInstance = Cast<UNewGameInstance>(GameInstance);
		if (NewGameInstance) {
			CurrentLevelIndex = NewGameInstance->CurrentLevelIndex;
		}
	}

	StartWave();
}

void ANewGameState::StartWave() {
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	SpawnedItems.Empty();

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	for (int32 i = 0; i < ItemToSpawn[CurrentWaveIndex]; ++i) {
		if (FoundVolumes.Num() > 0) {
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (SpawnVolume) {
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				if (SpawnedActor) {
					SpawnedItems.Add(SpawnedActor);
					if (SpawnedActor->IsA(ACoinItem::StaticClass())) {
						SpawnedCoinCount++;
					}
				}
			}
		}
	}

	if (CurrentWaveIndex == 1) {
		TArray<AActor*> FoundSpikeVolumes;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpikeSpawnVolume::StaticClass(), FoundSpikeVolumes);

		for (AActor* Actor : FoundSpikeVolumes) {
			if (ASpikeSpawnVolume* SpikeVolume = Cast<ASpikeSpawnVolume>(Actor)) {
				UE_LOG(LogTemp, Warning, TEXT("Spike 积己"));
				SpikeVolume->SpawnSpike();
			}
		}
	}

	if (CurrentWaveIndex == 2) {
		TArray<AActor*> FoundExplosionVolumes;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AExplosionSpawnVolume::StaticClass(), FoundExplosionVolumes);

		for (AActor* Actor : FoundExplosionVolumes) {
			if (AExplosionSpawnVolume* ExplosionVolume = Cast<AExplosionSpawnVolume>(Actor)) {
				UE_LOG(LogTemp, Warning, TEXT("Explosion 积己"));
				ExplosionVolume->LoopSpawnExplosion();
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Wave %d 矫累"), CurrentWaveIndex + 1);

	GetWorldTimerManager().SetTimer(
		WaveTimerHandle,
		this,
		&ANewGameState::OnWaveTimeUp,
		WaveDuration[CurrentWaveIndex],
		false
	);
}

void ANewGameState::OnWaveTimeUp() {
	EndWave();
}

void ANewGameState::OnCoinCollected() {
	CollectedCoinCount++;
	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"), CollectedCoinCount, SpawnedCoinCount);

	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount) {
		EndWave();
	}
}

void ANewGameState::EndLevel() {
	if (UGameInstance* GameInstance = GetGameInstance()) {
		UNewGameInstance* NewGameInstance = Cast<UNewGameInstance>(GameInstance);
		if (NewGameInstance) {
			CurrentLevelIndex++;
			NewGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= MaxLevel) {
		OnGameOver();
		return;
	}

	if (LevelMapNames.IsValidIndex(CurrentLevelIndex)) {
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else {
		OnGameOver();
	}
}

void ANewGameState::EndWave() {
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);

	for (AActor* Item : SpawnedItems) {
		if (IsValid(Item)) {
			Item->Destroy();
		}
	}

	SpawnedItems.Empty();
	CurrentWaveIndex++;

	if (CurrentWaveIndex >= MaxWave) {
		EndLevel();
	}
	else {
		StartWave();
	}
}

void ANewGameState::OnGameOver() {
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		if (ANewPlayerController* NewPlayerController = Cast<ANewPlayerController>(PlayerController)) {
			NewPlayerController->SetPause(true);
			NewPlayerController->ShowMainMenu(true);
		}
	}
}

void ANewGameState::UpdateHUD() {
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		if (ANewPlayerController* NewPlayerController = Cast<ANewPlayerController>(PlayerController)) {
			if (UUserWidget* HUDWidget = NewPlayerController->GetHUDWidget()) {
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time")))) {
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(WaveTimerHandle);
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time %.1fs"), RemainingTime)));
				}

				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score")))) {
					if (UGameInstance* GameInstance = GetGameInstance()) {
						UNewGameInstance* NewGameInstance = Cast<UNewGameInstance>(GameInstance);
						if (NewGameInstance) {
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score %d"), NewGameInstance->TotalScore)));
						}
					}
				}

				if (UTextBlock* LevelWaveIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level")))) {
					LevelWaveIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level %d - %d"), CurrentLevelIndex + 1, CurrentWaveIndex + 1)));
				}

				if (ANewCharacter* PlayerCharacter = Cast<ANewCharacter>(PlayerController->GetPawn())) {
					if (UTextBlock* DebuffText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Debuff")))) {
						FString DebuffString;
						DebuffString += FString::Printf(TEXT("Debuff\n"));

						if (PlayerCharacter->IsSlowed()) {
							float RemainingSlowingTime = FMath::Max(0.0f, PlayerCharacter->GetRemainingSlowTime());
							DebuffString += FString::Printf(TEXT("Slow %.1fs\n"), RemainingSlowingTime);
						}

						if (PlayerCharacter->IsReversed()) {
							float RemainingReverseTime = FMath::Max(0.0f, PlayerCharacter->GetRemainingReverseTime());
							DebuffString += FString::Printf(TEXT("Reverse %.1fs\n"), RemainingReverseTime);
						}

						if (PlayerCharacter->IsBlinded()) {
							float RemainingBlindTime = FMath::Max(0.0f, PlayerCharacter->GetRemainingBlindTime());
							DebuffString += FString::Printf(TEXT("Blind %.1fs\n"), RemainingBlindTime);
						}

						DebuffText->SetText(FText::FromString(DebuffString));
					}
				}
			}
		}
	}
}