// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CGCardPropertyBase.generated.h"

class UCGCardData_Base;
class ACGTile;

/**
 *  Base class for all card properties that can be added to a card
 *  if there is a need to add a new property to a card, create a new class that inherits from this class
 */
UCLASS(Abstract, BlueprintType, DefaultToInstanced, EditInlineNew, CollapseCategories, DisplayName = "Card Property")
class CARDGAME_API UCGCardPropertyBase : public UObject
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	
	/* ------------------------------------------ METHODS -------------------------------------------*/
public :
	UFUNCTION()
	virtual bool PreviewsBehaviors(ACGTile* TargetTile, APawn* CardOwner) { return false; }
	
	UFUNCTION()
	virtual bool Behaviors(ACGTile* TargetTile, APawn* CardOwner) { return false;}
};
