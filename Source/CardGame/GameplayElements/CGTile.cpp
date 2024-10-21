#include "CGTile.h"

#include "CardGame/Controls/CG_PlayerPawn.h"
#include "TileObject/CGTileObject_SpellItem.h"
#include "TileObject/CGTileObject_Unit.h"


ACGTile::ACGTile()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool ACGTile::CanSummonOnTile(ACG_PlayerPawn* Player) const
{
	// TODO Check if the player can summon on this tile
	// - Check if this a tile that is in his base  (if the player is the owner of the tile)
	return true;
}

bool ACGTile::CanPlaceObjectOnTile(ACG_PlayerPawn* Player) const
{
	switch(TileType)
	{
	case ETileType::Player1:
		if(Player->GetPlayerMultIndex() == 1)
			return true;
		break;
	case ETileType::Player2:
		if(Player->GetPlayerMultIndex() == 2)
			return true;
		break;
	case ETileType::Player3:
		if(Player->GetPlayerMultIndex() == 3)
			return true;
		break;
	case ETileType::Player4:
		if(Player->GetPlayerMultIndex() == 4)
			return true;
		break;
	default:
		return false;
	}
	return false;
}

bool ACGTile::CanMoveOnTile(ACGTileObject_Unit* lUnit, ACG_PlayerPawn* Player) const
{
	// TODO Check if the player can move on this tile
	// - Check if this a tile that is in his base (if the player is the owner of the tile)
	// - if there is no Object that block this Tile ?
	return true;
}

bool ACGTile::SummonOnTile(TSubclassOf<ACGTileObject_Unit> Class, ACG_PlayerPawn* Player)
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

bool ACGTile::PlaceObjectOnTile(TSubclassOf<ACGTileObject_SpellItem> Class, ACG_PlayerPawn* Player)
{
	if (!IsValid(Player) || !IsValid(Class) || !GetWorld()) {
		return false;
	}
	
	Objects.Add(GetWorld()->SpawnActor<ACGTileObject_SpellItem>(Class, GetActorLocation(), Player->GetActorRotation()));
	return true;
}

void ACGTile::BlueprintEditorTick(float DeltaTime)
{
	UpdateMaterial();
}

void ACGTile::UpdateMaterial()
{
		
	if(TileType != PreviousTileType)
	{
		MeshComponent = FindComponentByClass<UStaticMeshComponent>();
		if (MeshComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No StaticMeshComponent found on %s"), *GetName());
			return;
		}
		switch(TileType)
		{
		case ETileType::Disabled:
			SetActorHiddenInGame(true);
			MeshComponent->SetMaterial(0, InactiveMaterial.Get());
			break;
		case ETileType::Normal:
			SetActorHiddenInGame(false);
			MeshComponent->SetMaterial(0, ActiveMaterial.Get());
			break;
		case ETileType::Player1:
			SetActorHiddenInGame(false);
			MeshComponent->SetMaterial(0, PlayerMaterial.Get());
			break;
		case ETileType::Player2:
			SetActorHiddenInGame(false);
			MeshComponent->SetMaterial(0, PlayerMaterial.Get());
			break;
		case ETileType::Player3:
			SetActorHiddenInGame(false);
			MeshComponent->SetMaterial(0, PlayerMaterial.Get());
			break;
		case ETileType::Player4:
			SetActorHiddenInGame(false);
			MeshComponent->SetMaterial(0, PlayerMaterial.Get());
			break;
		}
		PreviousTileType = TileType;
	}
}

void ACGTile::SetHighlighted()
{
	IsHighlighted = true;
	MeshComponent->SetMaterial(0, HighlightMaterial.Get());
}

void ACGTile::BeginPlay()
{
	Super::BeginPlay();
	UpdateMaterial();
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
	UpdateMaterial();
}

void ACGTile::OnHoverStart(ACG_PlayerPawn* Pawn)
{
	if(IsHighlighted)
	{
		UE_LOG(LogTemp, Warning, TEXT("HOVER TILE"));
		IsHovered = true;
		MeshComponent->SetMaterial(0, HoveredMaterial.Get());
	}
}

void ACGTile::OnHoverStop(ACG_PlayerPawn* Pawn)
{
	if(IsHovered)
	{
		IsHovered = false;
		if(IsHighlighted)
		{
			MeshComponent->SetMaterial(0, HighlightMaterial.Get());
		}
		else
		{
			switch(TileType)
			{
				case ETileType::Disabled:
					MeshComponent->SetMaterial(0, InactiveMaterial.Get());
					break;
				case ETileType::Normal:
					MeshComponent->SetMaterial(0, ActiveMaterial.Get());
					break;
				case ETileType::Player1:
					MeshComponent->SetMaterial(0, PlayerMaterial.Get());
					break;
				case ETileType::Player2:
					MeshComponent->SetMaterial(0, PlayerMaterial.Get());
					break;
				case ETileType::Player3:
					MeshComponent->SetMaterial(0, PlayerMaterial.Get());
					break;
				case ETileType::Player4:
					MeshComponent->SetMaterial(0, PlayerMaterial.Get());
					break;
			}
		}
	}
}

