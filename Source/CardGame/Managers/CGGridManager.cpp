#include "CGGridManager.h"

#include "CardGame/GameplayElements/CGTile.h"
#include "Kismet/GameplayStatics.h"


ACGGridManager::ACGGridManager()
{
	PrimaryActorTick.bCanEverTick = true;
	RowNum = 10;
	ColumnNum = 10;
	TileWidth = 1;
	TileSpacing = .3f;
}

void ACGGridManager::InitializeGrid()
{
	TArray<AActor*> tiles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACGTile::StaticClass(), tiles);
	for (const auto& tile : tiles)
	{
		tile->Destroy();
	}

	// Clear the grid array
	tiles.Empty();

	UE_LOG(LogTemp, Warning, TEXT("Initialization"));
	for (size_t i = 0; i < RowNum; i++)
	{
		for (size_t j = 0; j < ColumnNum; j++)
		{
			FActorSpawnParameters SpawnParams;
			FVector SpawnLocation = FVector(i * 100 * TileWidth + i * 100 * TileSpacing, j * 100 * TileWidth + j * 100 * TileSpacing, 0);
			FRotator SpawnRotation = FRotator(0, 0, 0);
			ACGTile* SpawnedTile = GetWorld()->SpawnActor<ACGTile>(TileBP, SpawnLocation, SpawnRotation, SpawnParams);
#if WITH_EDITOR
			SpawnedTile->SetActorLabel(FString::Printf(TEXT("Tile_%d_%d"), static_cast<int>(i), static_cast<int>(j)));
#endif
			SpawnedTile->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
			SpawnedTile->SetActorLocation(SpawnLocation);
			SpawnedTile->SetRow(i);
			SpawnedTile->SetColumn(i);
			SpawnedTile->SetActorScale3D(FVector(TileWidth, TileWidth, 1));
		}
	}
}

ACGTile* ACGGridManager::GetTile(int32 i, int32 j)
{
	return nullptr;
}

void ACGGridManager::BlueprintEditorTick(float DeltaTime)
{
#if WITH_EDITOR
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		BlueprintEditorTick(DeltaTime);
	}
#endif
}

bool ACGGridManager::ShouldTickIfViewportsOnly() const
{
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor && UseEditorTick)
	{
		return true;
	}
	
	return false;
}


void ACGGridManager::BeginPlay()
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


void ACGGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

