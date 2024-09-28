#include "Tile.h"

#include "TileObject/TileObject_Object.h"
#include "TileObject/TileObject_Unit.h"


ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool ATile::CanSummonOnTile(APawn* Player) const
{
	// TODO Check if the player can summon on this tile
	// - Check if this a tile that is in his base  (if the player is the owner of the tile)
	return true;
}

bool ATile::CanPlaceObjectOnTile(APawn* Player) const
{
	// TODO Check if the player can place an object on this tile
	// - Check if this a tile that is in his base  (if the player is the owner of the tile)
	// - Or if the tile is in the middle of the map
	return true;
}

bool ATile::CanMoveOnTile(ATileObject_Unit* Unit, APawn* Player) const
{
	// TODO Check if the player can move on this tile
	// - Check if this a tile that is in his base (if the player is the owner of the tile)
	// - if there is no Object that block this Tile ?
	return true;
}

bool ATile::SummonOnTile(TSubclassOf<ATileObject_Unit> Class, APawn* Player)
{
	if (!IsValid(Player) || !IsValid(Class) || !GetWorld()) {
		return false;
	}
	
	if (m_Unit != nullptr){
		m_Unit->DestroyObject(Player, m_Unit);
	}
	
	m_Unit = GetWorld()->SpawnActor<ATileObject_Unit>(Class, GetActorLocation(), Player->GetActorRotation());
	return true;
}

bool ATile::PlaceObjectOnTile(TSubclassOf<ATileObject_Object> Class, APawn* Player)
{
	if (!IsValid(Player) || !IsValid(Class) || !GetWorld()) {
		return false;
	}
	
	m_Objects.Add(GetWorld()->SpawnActor<ATileObject_Object>(Class, GetActorLocation(), Player->GetActorRotation()));
	return true;
}

void ATile::BlueprintEditorTick(float DeltaTime)
{
	if(m_IsActive != m_IsActiveChecker)
	{
		m_MeshComponent = FindComponentByClass<UStaticMeshComponent>();
		if (m_MeshComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No StaticMeshComponent found on %s"), *GetName());
			return;
		}
		if(m_IsActive)
		{
			SetActorHiddenInGame(false);
			m_MeshComponent->SetMaterial(0, m_ActiveMaterial.Get());
		}
		else
		{
			SetActorHiddenInGame(true);
			m_MeshComponent->SetMaterial(0, m_InactiveMaterial.Get());
		}
	}
	m_IsActiveChecker = m_IsActive;
	
}

void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ATile::ShouldTickIfViewportsOnly() const
{
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor && m_UseEditorTick)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
#if WITH_EDITOR
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		BlueprintEditorTick(DeltaTime);
	}
#endif
}

