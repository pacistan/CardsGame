// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CGGameState.generated.h"

class ACGPlayerSpawn;
class ACG_PlayerController;
class UCGBaseState;
/**
 * 
 */
UCLASS()
class CARDGAME_API ACGGameState : public AGameStateBase
{
	GENERATED_UCLASS_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	UPROPERTY()
	TObjectPtr<UCGBaseState> CurrentGameState;

	UPROPERTY()
	TObjectPtr<UCGBaseState> PreviousGameState;
	
	/**
	 *  Map of Player Controller Associate to Spawn
	 */
	UPROPERTY()
	TMap<TObjectPtr<ACG_PlayerController>, TObjectPtr<ACGPlayerSpawn>> SpawnOfPlayerMap;
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
protected:

public:
	UFUNCTION()
	void AddPlayerToMap(TObjectPtr<ACG_PlayerController> PlayerController, TObjectPtr<ACGPlayerSpawn> PlayerSpawn);
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
};
