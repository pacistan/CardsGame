// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseState.generated.h"


UCLASS(Abstract)
class CARDGAME_ICAN_5JV_1_API UBaseState : public UObject
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
	/* ------------------------------------------ FUNCTIONS -----------------------------------------*/
public:
	UFUNCTION()
	virtual void OnEnterState();

	UFUNCTION()
	virtual void OnExitState();
	
	/* ------------------------------------------ OVERRIDE -----------------------------------------*/
	/* ------------------------------------------ STATIC -----------------------------------------*/
public:
	UFUNCTION()
	static UBaseState* MakeStateWithClass(TSubclassOf<UBaseState> NewStateClass, UObject* Outer);
};
