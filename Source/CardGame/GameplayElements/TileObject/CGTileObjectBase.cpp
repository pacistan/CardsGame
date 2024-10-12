// Fill out your copyright notice in the Description page of Project Settings.


#include "CGTileObjectBase.h"
#include "CardGame/Macro/CGLogMacro.h"


ACGTileObjectBase::ACGTileObjectBase(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("Mesh"));
}

void ACGTileObjectBase::Initialize(ACGTile* lOwner, APawn* lPlayer)
{
	TileOwner = lOwner;
	PLayerOwner = lPlayer;
	
	OnSpawn(); 
}

void ACGTileObjectBase::DestroyObject(APawn* player, ACGTileObjectBase* objectInstigator)
{
	// TODO : Add the logic of the object destruction
	// For now, we just log the destruction
	OnDeath();
	
	if (IsValid(objectInstigator)) {
		DEBUG_LOG("%s is destroyed by %s with %s", *GetName(), *player->GetName() ,*objectInstigator->GetName());
		return;
	} 
	DEBUG_LOG("%s is destroyed by %s ", *GetName(), *player->GetName());
}

void ACGTileObjectBase::OnSelected(APawn* player)
{
	// TODO : Show Widget with info of the object on Player Screen
	DEBUG_LOG("%s is selected by %s", *GetName(), *player->GetName());
}


