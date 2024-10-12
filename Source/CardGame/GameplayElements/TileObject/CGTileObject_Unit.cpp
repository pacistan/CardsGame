// Fill out your copyright notice in the Description page of Project Settings.


#include "CGTileObject_Unit.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_UNIT, "TileObject.Type.Unit");

ACGTileObject_Unit::ACGTileObject_Unit(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ObjectType = TAG_UNIT;
}

void ACGTileObject_Unit::OnSelected(APawn* player)
{
	Super::OnSelected(player);
}




