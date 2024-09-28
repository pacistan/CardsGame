// Fill out your copyright notice in the Description page of Project Settings.


#include "TileObjectBase.h"

#include "CardGame_ICAN_5JV_1/GameplayElements/Tile.h"
#include "CardGame_ICAN_5JV_1/Macro/LogMacro.h"


ATileObjectBase::ATileObjectBase(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("Mesh"));
}

void ATileObjectBase::OnSpawned(ATile* TileOwner, APawn* Player)
{
	m_TileOwner = TileOwner;
	m_PLayerOwner = Player;
}

void ATileObjectBase::DestroyObject(APawn* Player, ATileObjectBase* ObjectInstigator)
{
	if (IsValid(ObjectInstigator)) {
		LOG_LOG("%s is destroyed by %s with %s", *GetName(), *Player->GetName() ,*ObjectInstigator->GetName());
		return;
	}
	LOG_LOG("%s is destroyed by %s ", *GetName(), *Player->GetName());
}



