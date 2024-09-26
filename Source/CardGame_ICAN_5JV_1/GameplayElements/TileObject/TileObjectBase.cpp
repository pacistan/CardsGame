// Fill out your copyright notice in the Description page of Project Settings.


#include "TileObjectBase.h"

#include "CardGame_ICAN_5JV_1/GameplayElements/Tile.h"


ATileObjectBase::ATileObjectBase(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	// Constructor
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("Mesh"));
}



