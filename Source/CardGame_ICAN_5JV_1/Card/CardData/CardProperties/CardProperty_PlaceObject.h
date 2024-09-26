// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardPropertyBase.h"
#include "CardProperty_PlaceObject.generated.h"

/**
 * 
 */
UCLASS()
class CARDGAME_ICAN_5JV_1_API UCardProperty_PlaceObject : public UCardPropertyBase
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
	/* ------------------------------------------ METHODS -------------------------------------------*/
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
public:
	virtual bool Behvaviors(ATile* TargetTile) override;
};
