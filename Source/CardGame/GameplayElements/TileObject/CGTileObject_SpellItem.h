// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "CGTileObjectBase.h"
#include "CGTileObject_SpellItem.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_OBJECT)
/**
 *	Class for the Object that are Objects
 *		- Objects do not possess Movement
 *		- Can only be Placed on the center Board
 */
UCLASS()
class CARDGAME_API ACGTileObject_SpellItem : public ACGTileObjectBase
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	/* ------------------------------------------ METHODS -------------------------------------------*/
public:
	ACGTileObject_SpellItem(const FObjectInitializer& ObjectInitializer);
	
};
