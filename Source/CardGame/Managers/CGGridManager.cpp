#include "CGGridManager.h"

#include "CardGame/GameplayElements/CGTile.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"


ACGGridManager::ACGGridManager(): UseEditorTick(true)
{
	PrimaryActorTick.bCanEverTick = true;
	RowNum = 10;
	ColumnNum = 10;
	TileWidth = 1;
	TileSpacing = .3f;
}

void ACGGridManager::HighlightTiles(ETileType tileType)
{
	for(auto& Tile : TileTypeMap[tileType])
	{
		GridTiles[Tile.A][Tile.B]->SetHighlighted();
	}
}

void ACGGridManager::InitializeGrid(TArray<ACGTile*> FileTileArray)
{
	TArray<AActor*> tiles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACGTile::StaticClass(), tiles);
	for (const auto& tile : tiles)
	{
		tile->Destroy();
	}

	// Clear the grid array
	tiles.Empty();
	GridTiles.SetNum(RowNum);

	if(!FileTileArray.IsEmpty())
	{
		TileTypeMap.Add(ETileType::Player1, TArray<UE::Geometry::FIndex2i>());
		TileTypeMap.Add(ETileType::Player2, TArray<UE::Geometry::FIndex2i>());
		TileTypeMap.Add(ETileType::Player3, TArray<UE::Geometry::FIndex2i>());
		TileTypeMap.Add(ETileType::Player4, TArray<UE::Geometry::FIndex2i>());
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Initialization"));
	for (size_t i = 0; i < RowNum; i++)
	{
		GridTiles[i].SetNum(ColumnNum);
		for (size_t j = 0; j < ColumnNum; j++)
		{
			FVector SpawnLocation = FVector(i * 100 * TileWidth + i * 100 * TileSpacing, j * 100 * TileWidth + j * 100 * TileSpacing, 0);
			FRotator SpawnRotation = FRotator(0, 0, 0);
			FActorSpawnParameters SpawnParams;
			GridTiles[i][j] = GetWorld()->SpawnActor<ACGTile>(TileBP, SpawnLocation, SpawnRotation, SpawnParams);
			GridTiles[i][j]->SetActorScale3D(FVector(TileWidth, TileWidth, 1));
#if WITH_EDITOR
			GridTiles[i][j]->SetActorLabel(FString::Printf(TEXT("Tile_%d_%d"), static_cast<int>(i), static_cast<int>(j)));
#endif
			GridTiles[i][j]->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
			GridTiles[i][j]->SetActorLocation(SpawnLocation);
			GridTiles[i][j]->SetRow(i);
			GridTiles[i][j]->SetColumn(i);
			if(!FileTileArray.IsEmpty())
			{
				GridTiles[i][j]->SetTileType(FileTileArray[i * GridTiles.Num() +  j]->TileType);
				if(TileTypeMap.Contains(GridTiles[i][j]->TileType))
				{
					TileTypeMap[GridTiles[i][j]->TileType].Add(UE::Geometry::FIndex2i(i, j));
				}
			}
		}
	}
}

ACGTile* ACGGridManager::GetTile(int32 i, int32 j)
{
	return GridTiles[i][j];
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
	LoadRandomTileArrayFromFile();
}


void ACGGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACGGridManager::SaveTileArrayToFile()
{
	// Create a binary archive to save data
	TArray<uint8> BinaryArray;
	FMemoryWriter Ar(BinaryArray, true);

	TArray<ACGTile*> TileArray;
	TileArray.SetNum(GridTiles.Num() * GridTiles[0].Num());

	for (int32 i = 0; i < TileArray.Num(); i++)
	{
		int32 x = FMath::FloorToInt(float(i / GridTiles[0].Num()));
		int32 y = i % GridTiles[0].Num();
		TileArray[i] = GridTiles[x][y];
	}

	FString FilePath = FPaths::ProjectSavedDir() + "SavedData/" + FileName + ".bin";

	// Use FObjectAndNameAsStringProxyArchive for UObject* serialization
	FObjectAndNameAsStringProxyArchive SaveAr(Ar, false);  // false for saving
	SaveAr.ArIsSaveGame = true;  // Optional: mark this as a save game archive

	// Call your custom serialization function
	SaveTileArray(SaveAr, TileArray);

	// Save the binary data to a file
	FFileHelper::SaveArrayToFile(BinaryArray, *FilePath);
}

void ACGGridManager::SaveTileArray(FArchive& Ar, TArray<ACGTile*>& ClassArray)
{
	// Serialize the number of elements first
	int32 Num = ClassArray.Num();
	Ar << Num;

	// Then serialize each UObject* element in the array
	for (int32 i = 0; i < Num; i++)
	{
		Ar << ClassArray[i];  // This now handles proper UObject* serialization
	}
}

void ACGGridManager::LoadTileArrayFromFile()
{
	if(ListOfLoadableGridFiles.IsEmpty() || ListOfLoadableGridFiles.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No Load files in List"));
		return;
	}
	TArray<uint8> BinaryArray;
	FString FilePath = FPaths::ProjectSavedDir() + "SavedData/" + ListOfLoadableGridFiles[0] + ".bin";

	if (FFileHelper::LoadFileToArray(BinaryArray, *FilePath))
	{
		FMemoryReader Ar(BinaryArray, true);
		FObjectAndNameAsStringProxyArchive LoadAr(Ar, true);  // true for loading
		LoadAr.ArIsSaveGame = true;  // Optional

		TArray<ACGTile*> TileArray;
		LoadTileArray(LoadAr, TileArray);

		RowNum = TileArray.Last()->GetRow() + 1;
		ColumnNum = TileArray.Last()->GetColumn() + 1;

		InitializeGrid(TileArray);
	}
}

void ACGGridManager::LoadRandomTileArrayFromFile()
{
	if(ListOfLoadableGridFiles.IsEmpty() || ListOfLoadableGridFiles.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No Load files in List"));
		return;
	}
	TArray<uint8> BinaryArray;
	int32 randomIndex = FMath::RandRange(0, ListOfLoadableGridFiles.Num() - 1);

	FString FilePath = FPaths::ProjectSavedDir() + "SavedData/" + ListOfLoadableGridFiles[0] + ".bin";

	if (FFileHelper::LoadFileToArray(BinaryArray, *FilePath))
	{
		FMemoryReader Ar(BinaryArray, true);
		FObjectAndNameAsStringProxyArchive LoadAr(Ar, true);  // true for loading
		LoadAr.ArIsSaveGame = true;  // Optional

		TArray<ACGTile*> TileArray;
		LoadTileArray(LoadAr, TileArray);

		if(TileArray.IsEmpty())
			return;	
		RowNum = TileArray.Last()->GetRow() + 1;
		ColumnNum = TileArray.Last()->GetColumn() + 1;

		InitializeGrid(TileArray);
	}
}

void ACGGridManager::LoadTileArray(FArchive& Ar, TArray<ACGTile*>& ClassArray)
{
	int32 Num = 0;
	Ar << Num;

	ClassArray.SetNum(Num);

	for (int32 i = 0; i < Num; i++)
	{
		Ar << ClassArray[i];  // Proper UObject* deserialization
	}
}

