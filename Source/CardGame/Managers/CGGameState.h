// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardGame/Macro/CGGetSetMacro.h"
#include "CardGame/Player/CGPlayerPawn.h"
#include "GameFramework/GameStateBase.h"
#include "CGGameState.generated.h"

class ACGPlayerStart;
class APlayerStart;
class ACG_PlayerController;
class UCGBaseState;
/**
 * 
 */
UCLASS()
class CARDGAME_API ACGGameState : public AGameStateBase
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	UPROPERTY(EditDefaultsOnly, Category = "CGGameState|Default")
	TSubclassOf<ACGPlayerPawn> DefaultPawnClass;
	
	UPROPERTY()
	TObjectPtr<UCGBaseState> CurrentGameState;

	UPROPERTY()
	TObjectPtr<UCGBaseState> PreviousGameState;
	
	/**
	 *  Map of Player Controller Associate to Spawn
	 */
	TMap<TObjectPtr<ACG_PlayerController>, TObjectPtr<ACGPlayerStart>> SpawnOfPlayerMap;
	
	UPROPERTY(Replicated)
	float ServerFPS;

private:
	UPROPERTY(Transient)
	TArray<TWeakObjectPtr<ACGPlayerStart>> CachedPlayerStarts;
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
protected:
	APlayerStart* GetFirstRandomUnoccupiedPlayerStart(AController* Controller, const TArray<ACGPlayerStart*>& FoundStartPoints) const;
	
public:
	ACGGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	void AddPlayerToMap(TObjectPtr<ACG_PlayerController> PlayerController, TObjectPtr<ACGPlayerStart> PlayerSpawn);

	const TSubclassOf<ACGPlayerPawn> GetDefaultPawnClass() { return DefaultPawnClass; }
	
	DECLARE_GETTER(ServerFPS, ServerFPS, float);
	
private:
	AActor* ChoosePlayerStart(AController* Player);
	bool ControllerCanRestart(AController* Player);
	void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation);
	friend class ACGGameMode;
	
#if WITH_EDITOR
	APlayerStart* FindPlayFromHereStart(AController* Player);
#endif

	void HandleOnActorSpawned(AActor* SpawnedActor);
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
public:
	virtual void Tick(float DeltaSeconds) override;
	
private:
	virtual void PostInitializeComponents() override;
};
