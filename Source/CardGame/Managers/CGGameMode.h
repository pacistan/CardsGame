#pragma once

#include "CoreMinimal.h"
#include "CardGame/Macro/CGGetSetMacro.h"
#include "GameFramework/GameModeBase.h"
#include "CardGame/Macro/CGGetSetMacro.h"
#include "CGGameMode.generated.h"

class ACGPlayerStart;
class ACGPlayerSpawn;
class ACG_PlayerController;
class ACG_DeckActor;
class UCGBaseState;
class ACGPlayerPawn;
class UCG_FSM;
class AGridManager;

/**
 * Post Login Event, Trigger When a player joins the game
 *
 * Call at end Of initialization 
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCGGameModePlayerInitialized, AGameModeBase*, AController*)

UCLASS()
class CARDGAME_API ACGGameMode : public AGameModeBase
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UCG_FSM> FSM;

	UPROPERTY()
	TArray<TObjectPtr<ACGPlayerPawn>> Players;

	UPROPERTY()
	TArray<TObjectPtr<ACG_DeckActor>> Decks;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCGBaseState> StartState;

public:
	// Delegate called on player initialization
	FOnCGGameModePlayerInitialized OnGameModePlayerInitialized;
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
protected:
	void HostDedicatedServer();
	
public:
	ACGGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	void RegisterPlayerPawn(ACGPlayerPawn* Player);

	// Restart (respawn) the specified player or bot next frame
	// - If bForceReset is true, the controller will be reset this frame (abandoning the currently possessed pawn, if any)
	UFUNCTION(BlueprintCallable)
	void RequestPlayerRestartNextFrame(AController* Controller, bool bForceReset = false);
	
	DECLARE_GETTER(FSM, FSM, TObjectPtr<UCG_FSM>);
	DECLARE_GETTER(PlayerPawn, Players, TArray<TObjectPtr<ACGPlayerPawn>>);
	DECLARE_GETTER(StartState, StartState, TSubclassOf<UCGBaseState>);
	
	FORCEINLINE ACG_DeckActor* GetDeck(int PlayerIndex)
	{
		if (!Decks.IsEmpty() && Decks.Num() > 0)
			return Decks[PlayerIndex];
		return nullptr;
	}

	UFUNCTION(BlueprintCallable, Category = "CG|Pawn")
	TSubclassOf<ACGPlayerPawn> GetPawnClassForController(const AController* InController) const;
	
	/* ------------------------------------------ OVERRIDE -------------------------------------------*/
	virtual void BeginPlay() override;

	//~AGameModeBase interface
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
	virtual bool ShouldSpawnAtStartSpot(AController* Player) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation) override;
	virtual bool PlayerCanRestart_Implementation(APlayerController* Player) override;
	virtual void InitGameState() override;
	virtual bool UpdatePlayerStartSpot(AController* Player, const FString& Portal, FString& OutErrorMessage) override;
	virtual void GenericPlayerInitialization(AController* NewPlayer) override;
	virtual void FailedToRestartPlayer(AController* NewPlayer) override;
	//~End of AGameModeBase interface
	
	
};
