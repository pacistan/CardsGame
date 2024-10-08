// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CardPropertyBase.generated.h"

/**
 *  Base class for all card properties that can be added to a card
 *  if there is a need to add a new property to a card, create a new class that inherits from this class
 */
UCLASS(Abstract, BlueprintType, DefaultToInstanced, EditInlineNew, CollapseCategories, DisplayName = "Card Property")
class CARDGAME_ICAN_5JV_1_API UCardPropertyBase : public UObject
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	
	/* ------------------------------------------ METHODS -------------------------------------------*/
public :
	// TODO : add Tile as a parameter to the function
	UFUNCTION()
	virtual bool PreviewsBehvaviors() { return false; }
	
	// TODO : add Tile as a parameter to the function
	UFUNCTION()
	virtual bool Behvaviors() { return false; }
};
