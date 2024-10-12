// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CGCardPropertyBase.h"
#include "CGCardProperty_Summon.generated.h"

class ACGTileObject_Unit;

/**
 *  Property to summon a unit on the board
 */
UCLASS(DisplayName = "Summon")
class CARDGAME_API UCGCardProperty_Summon : public UCGCardPropertyBase
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACGTileObject_Unit> CardObjectClassToSummon;
	/* ------------------------------------------ METHODS -------------------------------------------*/
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
protected:
	virtual bool Behaviors(ACGTile* TargetTile, APawn* CardOwner) override;
};
