// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "CGTileObjectBase.h"
#include "CGTileObject_Unit.generated.h"

class UCGMovementPatternBase;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CG|Movement")
	TSoftClassPtr<UCGMovementPatternBase> MovementPattern; 
	/* ------------------------------------------ METHODS -------------------------------------------*/
public:
	ACGTileObject_Unit(const FObjectInitializer& ObjectInitializer);

	/* ------------------------------------------ OVERRIDES -------------------------------------------*/

protected:
	
	// TODO : Function for Preview Movement 
	virtual void OnSelected(APawn* player) override;
};
