// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardGame/Macro/CGGetSetMacro.h"
#include "GameFramework/PlayerState.h"
#include "CGPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CARDGAME_API ACGPlayerState : public APlayerState
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	// Class to instantiate for this pawn (need to derive if ACGPlayerPawn)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CG|Pawn")
	TSubclassOf<APawn> PawnClass;
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
public:
	DECLARE_GETTER(PawnClass, PawnClass, TSubclassOf<APawn>)
	/* ------------------------------------------ OVERRIDE -------------------------------------------*/
};
