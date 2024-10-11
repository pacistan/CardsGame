// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CGBaseState.generated.h"


UCLASS(Abstract)
class CARDGAME_API UCGBaseState : public UObject
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
	static UCGBaseState* MakeStateWithClass(TSubclassOf<UCGBaseState> NewStateClass, UObject* Outer);
};
