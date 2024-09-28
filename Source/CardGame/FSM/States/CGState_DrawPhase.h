// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CGBaseState.h"
#include "UObject/Object.h"
#include "CGState_DrawPhase.generated.h"


class APlayerPawn;
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnDrawEnd, APlayerPawn*, PlayerTarget);

UCLASS()
class CARDGAME_API UCGState_DrawPhase : public UCGBaseState
{
	GENERATED_BODY()

	TArray<TObjectPtr<APlayerPawn>> m_Players;

	FOnDrawEnd m_DrawEndDelegate;

	virtual void Initialization(AGameMode_Gameplay* GameMode) override;
	virtual void OnEnterState() override;
	void OnDrawEnd(APlayerPawn*		PlayerPawn);
};
