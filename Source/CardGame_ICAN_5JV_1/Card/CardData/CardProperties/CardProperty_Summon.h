// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardPropertyBase.h"
#include "CardProperty_Summon.generated.h"

class ATileObject_Unit;

/**
 *  Property to summon a unit on the board
 */
UCLASS(DisplayName = "Summon")
class CARDGAME_ICAN_5JV_1_API UCardProperty_Summon : public UCardPropertyBase
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATileObject_Unit> m_CardObjectClassToSummon;
	/* ------------------------------------------ METHODS -------------------------------------------*/
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
protected:
	virtual bool Behvaviors(ATile* TargetTile, APawn* CardOwner) override;
};
