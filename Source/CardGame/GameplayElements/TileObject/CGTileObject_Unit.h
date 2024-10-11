// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "CGTileObjectBase.h"
#include "CGTileObject_Unit.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UNIT);

/**
 *	Class for the Object that are Units
 *		- Units possess Movement
 *		- Can only be Placed on the Board Side of the Player
 */
UCLASS()
class CARDGAME_API ACGTileObject_Unit : public ACGTileObjectBase
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	// TODO Patern and Range of movement
	/* ------------------------------------------ METHODS -------------------------------------------*/
public:
	ACGTileObject_Unit(const FObjectInitializer& ObjectInitializer);
	
	// TODO : Function to move the unit
	// TODO : Function for Preview Movement
	
};
