// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CGCardPropertyBase.h"
#include "CGCardProperty_PlaceObject.generated.h"

/**
 * 
 */
UCLASS()
class CARDGAME_API UCGCardProperty_PlaceObject : public UCGCardPropertyBase
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
	/* ------------------------------------------ METHODS -------------------------------------------*/
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
public:
	virtual bool Behvaviors(ACGTile* TargetTile, APawn* CardOwner) override;
};
