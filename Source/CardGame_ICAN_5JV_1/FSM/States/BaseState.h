// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseState.generated.h"


class AGameMode_Gameplay;

UCLASS(Abstract)
class CARDGAME_ICAN_5JV_1_API UBaseState : public UObject
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	TObjectPtr<AGameMode_Gameplay> m_GameMode; 
	
	/* ------------------------------------------ FUNCTIONS -----------------------------------------*/
public:
	UFUNCTION()
	virtual void Initialization(AGameMode_Gameplay* GameMode);
	
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
	static UBaseState* MakeStateWithClass(TSubclassOf<UBaseState> NewStateClass, UObject* Outer);
};
