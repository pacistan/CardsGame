// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CGCardPropertyBase.h"
#include "CGCardProperty_Move.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "Move")
class CARDGAME_API UCGCardProperty_Move : public UCGCardPropertyBase
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
	/* ------------------------------------------ METHODS -------------------------------------------*/
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
protected:
	virtual bool Behaviors(ACGTile* TargetTile, APawn* CardOwner) override;
};
