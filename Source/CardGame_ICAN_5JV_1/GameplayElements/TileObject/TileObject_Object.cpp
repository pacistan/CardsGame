// Fill out your copyright notice in the Description page of Project Settings.


#include "TileObject_Object.h"


UE_DEFINE_GAMEPLAY_TAG(TAG_OBJECT, "TileObject.Type.Object");

ATileObject_Object::ATileObject_Object(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	m_ObjectType = TAG_OBJECT;
}

