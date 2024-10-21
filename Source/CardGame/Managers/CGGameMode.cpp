﻿#include "CGGameMode.h"
#include "CGGameMode.h"

#include "CGGameState.h"
#include "EngineUtils.h"
#include "GameMapsSettings.h"
#include "CardGame/Card/Deck/CG_DeckActor.h"
#include "CardGame/Player/CGPlayerPawn.h"
#include "CardGame/FSM/States/CG_FSM.h"
#include "CardGame/Macro/CGLogMacro.h"
#include "CardGame/Player/CGPlayerStart.h"
#include "CardGame/Player/CGPlayerState.h"
#include "CardGame/Player/CG_PlayerController.h"
#include "CardGame/Subsystem/CGHostServerSubsytem.h"
#include "Engine/PlayerStartPIE.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


ACGGameMode::ACGGameMode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	GameStateClass = ACGGameState::StaticClass();
	PlayerControllerClass = ACG_PlayerController::StaticClass();
	PlayerStateClass = ACGPlayerState::StaticClass();
	DefaultPawnClass = ::ACGPlayerPawn::StaticClass();
	// TODO : set HUDClass
}

void ACGGameMode::HostDedicatedServer()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (ensure(GameInstance)) {
		UCGHostServerSubsytem* SessionSubsystem = GameInstance->GetSubsystem<UCGHostServerSubsytem>();
	}
}

TSubclassOf<ACGPlayerPawn> ACGGameMode::GetPawnClassForController(const AController* InController) const
{
	// See if pawn data is already set on the player state
	if (InController != nullptr){
		if (const ACGPlayerState* CGPS = InController->GetPlayerState<ACGPlayerState>()){
			if (TSubclassOf<ACGPlayerPawn> PawnClass = CGPS->PawnClass) {
				return PawnClass;
			}
		}
	}
	
	// If not, fall back to the the default from the GameState
	check(GameState);
	if(ACGGameState* CGGameState = Cast<ACGGameState>(GameState)) {
		return CGGameState->GetDefaultPawnClass();
	}

	return nullptr;
}

void ACGGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> PlayerActors;
	TArray<AActor*> DeckActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACGPlayerPawn::StaticClass(), PlayerActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACG_DeckActor::StaticClass(), DeckActors);
	
	Decks.SetNum(DeckActors.Num());
	for(int i = 0; i < DeckActors.Num(); i++)
	{
		Decks[i] = Cast<ACG_DeckActor>(DeckActors[i]);
	}
	
	Players.SetNum(PlayerActors.Num());
	for(int i = 0; i < PlayerActors.Num(); i++)
	{
		Players[i] = Cast<ACGPlayerPawn>(PlayerActors[i]);
	}
	
	FSM = NewObject<UCG_FSM>(this);
	FSM->Initialize(this);

	
}

void ACGGameMode::RegisterPlayerPawn(ACGPlayerPawn* Player)
{
	Players.Add(Player);
}

void ACGGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

UClass* ACGGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController != nullptr) {
		if (const ACGPlayerState* CGPS = InController->GetPlayerState<ACGPlayerState>()) {
			if (CGPS->PawnClass) {
				return CGPS->PawnClass;
			}
		}
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

APawn* ACGGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;	// Never save the default player pawns into a map.
	SpawnInfo.bDeferConstruction = true;
	
	if (UClass* PawnClass = GetDefaultPawnClassForController(NewPlayer)) {
		if (APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnClass, SpawnTransform, SpawnInfo)) {
			SpawnedPawn->FinishSpawning(SpawnTransform);
			return SpawnedPawn;
		} else {
			DEBUG_ERROR("Game mode was unable to spawn Pawn of class [%s] at [%s].", *GetNameSafe(PawnClass), *SpawnTransform.ToHumanReadableString());
		}
	} else {
		DEBUG_ERROR("Game mode was unable to spawn Pawn due to NULL pawn class.");
	}

	return nullptr;
}

bool ACGGameMode::ShouldSpawnAtStartSpot(AController* Player)
{
	// Don't put AnyCode Here
	return false;
}

void ACGGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}

AActor* ACGGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if (ACGGameState* CGGameState = Cast<ACGGameState>(GameState)) {
		return CGGameState->ChoosePlayerStart(Player);
	}
	return Super::ChoosePlayerStart_Implementation(Player);
}

void ACGGameMode::FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation)
{
	if (ACGGameState* CGGameState = Cast<ACGGameState>(GameState)) {
		return CGGameState->FinishRestartPlayer(NewPlayer, StartRotation);
	}
	Super::FinishRestartPlayer(NewPlayer, StartRotation);
}

bool ACGGameMode::PlayerCanRestart_Implementation(APlayerController* Player)
{
	return Super::PlayerCanRestart_Implementation(Player);
}

void ACGGameMode::InitGameState()
{
	Super::InitGameState();

	// Spawn any players that are already attached
	// TODO: Here we're handling only *player* controllers, but in GetDefaultPawnClassForController_Implementation we skipped all controllers
	// GetDefaultPawnClassForController_Implementation might only be getting called for players anyways
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator) {
		APlayerController* PC = Cast<APlayerController>(*Iterator);
		if ((PC != nullptr) && (PC->GetPawn() == nullptr)) {
			if (PlayerCanRestart(PC)) {
				RestartPlayer(PC);
			}
		}
	}
}

bool ACGGameMode::UpdatePlayerStartSpot(AController* Player, const FString& Portal, FString& OutErrorMessage)
{
	// Do nothing, we'll wait until PostLogin when we try to spawn the player for real.
	// Doing anything right now is no good,
	return Super::UpdatePlayerStartSpot(Player, Portal, OutErrorMessage);
}

void ACGGameMode::GenericPlayerInitialization(AController* NewPlayer)
{
	Super::GenericPlayerInitialization(NewPlayer);
	
	OnGameModePlayerInitialized.Broadcast(this, NewPlayer);
}

void ACGGameMode::RequestPlayerRestartNextFrame(AController* Controller, bool bForceReset)
{
	if (bForceReset && (Controller != nullptr)) {
		Controller->Reset();
	}

	if (APlayerController* PC = Cast<APlayerController>(Controller)) {
		GetWorldTimerManager().SetTimerForNextTick(PC, &APlayerController::ServerRestartPlayer_Implementation);
	}
}

void ACGGameMode::FailedToRestartPlayer(AController* NewPlayer)
{
	Super::FailedToRestartPlayer(NewPlayer);

	// If we tried to spawn a pawn and it failed, lets try again *note* check if there's actually a pawn class
	// before we try this forever.
	if (UClass* PawnClass = GetDefaultPawnClassForController(NewPlayer)) {
		if (APlayerController* NewPC = Cast<APlayerController>(NewPlayer)) {
			// If it's a player don't loop forever, maybe something changed and they can no longer restart if so stop trying.
			if (PlayerCanRestart(NewPC)) {
				RequestPlayerRestartNextFrame(NewPlayer, false);			
			} else {
				UE_LOG(LogCard, Verbose, TEXT("FailedToRestartPlayer(%s) and PlayerCanRestart returned false, so we're not going to try again."), *GetPathNameSafe(NewPlayer));
			}
		} else {
			// For bot if there is 
			RequestPlayerRestartNextFrame(NewPlayer, false);
		}
	} else {
		UE_LOG(LogCard, Verbose, TEXT("FailedToRestartPlayer(%s) but there's no pawn class so giving up."), *GetPathNameSafe(NewPlayer));
	}
}


