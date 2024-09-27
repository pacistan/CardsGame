#include "GridManager.h"

#include "CardGame_ICAN_5JV_1/GameplayElements/Tile.h"
#include "Kismet/GameplayStatics.h"


AGridManager::AGridManager()
{
	PrimaryActorTick.bCanEverTick = true;
	m_RowNum = 10;
	m_ColumnNum = 10;
	m_TileWidth = 1;
	m_TileSpacing = .3f;
}

void AGridManager::InitializeGrid()
{
	TArray<AActor*> tiles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATile::StaticClass(), tiles);
	for (const auto& tile : tiles)
	{
		tile->Destroy();
	}

	// Clear the grid array
	tiles.Empty();

	UE_LOG(LogTemp, Warning, TEXT("Initialization"));
	for (size_t i = 0; i < m_RowNum; i++)
	{
		for (size_t j = 0; j < m_ColumnNum; j++)
		{
			FActorSpawnParameters SpawnParams;
			FVector SpawnLocation = FVector(i * 100 * m_TileWidth + i * 100 * m_TileSpacing, j * 100 * m_TileWidth + j * 100 * m_TileSpacing, 0);
			FRotator SpawnRotation = FRotator(0, 0, 0);
			ATile* SpawnedTile = GetWorld()->SpawnActor<ATile>(m_TileBP, SpawnLocation, SpawnRotation, SpawnParams);
#if WITH_EDITOR
			SpawnedTile->SetActorLabel(FString::Printf(TEXT("Tile_%d_%d"), static_cast<int>(i), static_cast<int>(j)));
#endif
			SpawnedTile->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
			SpawnedTile->SetActorLocation(SpawnLocation);
			SpawnedTile->SetRow(i);
			SpawnedTile->SetColumn(i);
			SpawnedTile->SetActorScale3D(FVector(m_TileWidth, m_TileWidth, 1));
		}
	}
}

ATile* AGridManager::GetTile(int32 i, int32 j)
{
	return nullptr;
}

void AGridManager::BlueprintEditorTick(float DeltaTime)
{
#if WITH_EDITOR
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		BlueprintEditorTick(DeltaTime);
	}
#endif
}

bool AGridManager::ShouldTickIfViewportsOnly() const
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


void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	return;
	TArray<AActor*> tiles;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATile::StaticClass(), tiles);
	m_GridTiles = *new TArray<FTileArray>[m_RowNum];
	for(auto tileArray : m_GridTiles)
	{
		tileArray.NestedTileArray = *new TArray<TObjectPtr<ATile>>[m_ColumnNum];
	}

	for(const auto item : tiles)
	{
		ATile* tile = Cast<ATile>(item);
		m_GridTiles[tile->GetRow()].NestedTileArray[tile->GetColumn()] = tile;
	}
}


void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

