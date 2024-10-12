// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CGBaseState.generated.h"


class ACGGameMode;

UCLASS(Abstract)
class CARDGAME_API UCGBaseState : public UObject
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	TObjectPtr<ACGGameMode> GameMode; 
	
	/* ------------------------------------------ FUNCTIONS -----------------------------------------*/
public:
	UFUNCTION()
	virtual void Initialization(ACGGameMode* GameMode);
	
	UFUNCTION()
	virtual void OnEnterState();

	UFUNCTION()
	virtual void OnStateTick(float DeltaTime);
	
	UFUNCTION()
	virtual void OnExitState();
	
	/* ------------------------------------------ OVERRIDE -----------------------------------------*/
	/* ------------------------------------------ STATIC -----------------------------------------*/
public:
	UFUNCTION()
	static UCGBaseState* MakeStateWithClass(TSubclassOf<UCGBaseState> NewStateClass, UObject* Outer);
};
