// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileObjectBase.h"
#include "TileObject_Object.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_OBJECT)
/**
 *	Class for the Object that are Objects
 *		- Objects do not possess Movement
 *		- Can only be Placed on the center Board
 */
UCLASS()
class CARDGAME_ICAN_5JV_1_API ATileObject_Object : public ATileObjectBase
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	/* ------------------------------------------ METHODS -------------------------------------------*/
public:
	ATileObject_Object(const FObjectInitializer& ObjectInitializer);
	
};
