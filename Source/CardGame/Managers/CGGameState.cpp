// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameState.h"

#include "CardGame/Player/CG_PlayerController.h"
#include "CardGame/Macro/CGLogMacro.h"

void ACGGameState::AddPlayerToMap(TObjectPtr<ACG_PlayerController> PlayerController, TObjectPtr<ACGPlayerSpawn> PlayerSpawn)
{
	if (!HasAuthority()) {
		return;
	}
	
	if (SpawnOfPlayerMap.Contains(PlayerController)) {
		return;
	}
	
	SpawnOfPlayerMap.Add(PlayerController, PlayerSpawn);
}
