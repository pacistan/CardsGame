// Fill out your copyright notice in the Description page of Project Settings.


#include "TileObject_Unit.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_UNIT, "TileObject.Type.Unit");

ATileObject_Unit::ATileObject_Unit(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	m_ObjectType = TAG_UNIT;
}


