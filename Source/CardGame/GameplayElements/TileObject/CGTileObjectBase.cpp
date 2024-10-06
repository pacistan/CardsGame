// Fill out your copyright notice in the Description page of Project Settings.


#include "CGTileObjectBase.h"
#include "CardGame/Macro/CGLogMacro.h"


ACGTileObjectBase::ACGTileObjectBase(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("Mesh"));
}

void ACGTileObjectBase::OnSpawned(ACGTile* TileOwner, APawn* Player)
{
	TileOwner = TileOwner;
	PLayerOwner = Player;
}

void ACGTileObjectBase::DestroyObject(APawn* Player, ACGTileObjectBase* ObjectInstigator)
{
	if (IsValid(ObjectInstigator)) {
		LOG_LOG("%s is destroyed by %s with %s", *GetName(), *Player->GetName() ,*ObjectInstigator->GetName());
		return;
	}
	LOG_LOG("%s is destroyed by %s ", *GetName(), *Player->GetName());
}



