// Fill out your copyright notice in the Description page of Project Settings.


#include "CGTileObject_SpellItem.h"


UE_DEFINE_GAMEPLAY_TAG(TAG_OBJECT, "TileObject.Type.Object");

ACGTileObject_SpellItem::ACGTileObject_SpellItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ObjectType = TAG_OBJECT;
}

