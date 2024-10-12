#include "CGTile.h"

#include "TileObject/CGTileObject_SpellItem.h"
#include "TileObject/CGTileObject_Unit.h"


ACGTile::ACGTile()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool ACGTile::CanSummonOnTile(APawn* Player) const
{
	// TODO Check if the player can summon on this tile
	// - Check if this a tile that is in his base  (if the player is the owner of the tile)
	return true;
}

bool ACGTile::CanPlaceObjectOnTile(APawn* Player) const
{
	// TODO Check if the player can place an object on this tile
	// - Check if this a tile that is in his base  (if the player is the owner of the tile)
	// - Or if the tile is in the middle of the map
	return true;
}


bool ACGTile::CanMoveOnTile(ACGTileObject_Unit* lUnit, APawn* lPlayer) const
{
	// TODO Check if the player can move on this tile
	// - Check if this a tile that is in his base (if the player is the owner of the tile)
	// - if there is no Object that block this Tile ?
	return true;
}

bool ACGTile::SummonOnTile(TSubclassOf<ACGTileObject_Unit> Class, APawn* Player)
{
	if (!IsValid(Player) || !IsValid(Class) || !GetWorld()) {
		return false;
	}
	
	if (Unit != nullptr){
		Unit->DestroyObject(Player, Unit);
	}
	
	Unit = GetWorld()->SpawnActor<ACGTileObject_Unit>(Class, GetActorLocation(), Player->GetActorRotation());
	return true;
}

bool ACGTile::PlaceObjectOnTile(TSubclassOf<ACGTileObject_SpellItem> Class, APawn* Player)
{
	if (!IsValid(Player) || !IsValid(Class) || !GetWorld()) {
		return false;
	}
	
	Objects.Add(GetWorld()->SpawnActor<ACGTileObject_SpellItem>(Class, GetActorLocation(), Player->GetActorRotation()));
	return true;
}

void ACGTile::BlueprintEditorTick(float DeltaTime)
{
	if(IsActive != IsActiveChecker)
	{
		MeshComponent = FindComponentByClass<UStaticMeshComponent>();
		if (MeshComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No StaticMeshComponent found on %s"), *GetName());
			return;
		}
		if(IsActive)
		{
			SetActorHiddenInGame(false);
			MeshComponent->SetMaterial(0, ActiveMaterial.Get());
		}
		else
		{
			SetActorHiddenInGame(true);
			MeshComponent->SetMaterial(0, InactiveMaterial.Get());
		}
	}
	IsActiveChecker = IsActive;
	
}

void ACGTile::BeginPlay()
{
	Super::BeginPlay();
}

bool ACGTile::ShouldTickIfViewportsOnly() const
{
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor && bUseEditorTick)
	{
		return true;
	}
	return false;
}

void ACGTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
#if WITH_EDITOR
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		BlueprintEditorTick(DeltaTime);
	}
#endif
}

