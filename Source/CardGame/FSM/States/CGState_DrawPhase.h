// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CGBaseState.h"
#include "UObject/Object.h"
#include "CGState_DrawPhase.generated.h"


class ACGPlayerPawn;
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnDrawEnd, ACGPlayerPawn*, PlayerTarget);

UCLASS()
class CARDGAME_API UCGState_DrawPhase : public UCGBaseState
{
	GENERATED_BODY()

	TArray<TObjectPtr<ACGPlayerPawn>> Players;

	FOnDrawEnd DrawEndDelegate;

	virtual void Initialization(ACGGameMode* GameMode) override;
	virtual void OnEnterState() override;

	UFUNCTION()
	void OnDrawEnd(ACGPlayerPawn* PlayerPawn);
};
