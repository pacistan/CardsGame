// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardGame_ICAN_5JV_1/Macro/GetSetMacro.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_Gameplay.generated.h"

class APlayerPawn;
class UFSM_Gameplay;
class AGridManager;

UCLASS()
class CARDGAME_ICAN_5JV_1_API AGameMode_Gameplay : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UFSM_Gameplay> m_FSM;

	UPROPERTY()
	TArray<TObjectPtr<APlayerPawn>> m_Players;
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
public:
	DECLARE_GETTER(FSM, m_FSM, TObjectPtr<UFSM_Gameplay>);
	DECLARE_GETTER(PlayerPawn, m_Players, TArray<TObjectPtr<APlayerPawn>>);

	void RegisterPlayerPawn(APlayerPawn* Player);

	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
	virtual void BeginPlay() override;
	
};
