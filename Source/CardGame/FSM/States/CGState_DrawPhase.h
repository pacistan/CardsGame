// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CGBaseState.h"
#include "UObject/Object.h"
#include "CGState_DrawPhase.generated.h"


class ACG_PlayerPawn;
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnDrawEnd, ACG_PlayerPawn*, PlayerTarget);

UCLASS()
class CARDGAME_API UCGState_DrawPhase : public UCGBaseState
{
	GENERATED_BODY()

	TArray<TObjectPtr<ACG_PlayerPawn>> m_Players;

	FOnDrawEnd m_DrawEndDelegate;

	virtual void Initialization(ACGGameMode* GameMode) override;
	virtual void OnEnterState() override;
	void OnDrawEnd(ACG_PlayerPawn* PlayerPawn);
};
