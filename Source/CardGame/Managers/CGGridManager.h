#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CGGridManager.generated.h"

enum class ETileType : uint32;
class ACGTile;
class ACGGameMode;

UCLASS()
class CARDGAME_API ACGGridManager : public AActor
{
	GENERATED_BODY()

	/* ------------------------------------------ MEMBERS -------------------------------------------*/
private:
	UPROPERTY(EditAnywhere, Category = "GM/Grid Generation Parameters")
	int32 RowNum;

	UPROPERTY(EditAnywhere, Category = "GM/Grid Generation Parameters")
	int32 ColumnNum;

	UPROPERTY(EditAnywhere, Category = "GM/Grid Generation Parameters")
	double TileWidth;

	UPROPERTY(EditAnywhere, Category = "GM/Grid Generation Parameters")
	double TileSpacing;
	
	UPROPERTY(EditAnywhere, Category = "GM/Grid Generation References")
	TSubclassOf<ACGTile> TileBP;

	TArray<TArray<TObjectPtr<ACGTile>>> GridTiles;

	UPROPERTY(EditAnywhere, Category = "GM/GridManager")
	bool UseEditorTick;

	UPROPERTY(EditAnywhere, Category = "GM/Grid Saving")
	FString FileName;

	UPROPERTY(EditAnywhere, Category = "GM/Grid Saving")
	TArray<FString> ListOfLoadableGridFiles;

	TMap<ETileType, TArray<UE::Geometry::FIndex2i>> TileTypeMap;
	
public:
	TArray<TArray<TObjectPtr<ACGTile>>> GetTiles() const {return GridTiles;};
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
public:
	ACGGridManager();

	UFUNCTION(CallInEditor, Category = "CG|Events")
	void InitializeEmptyGrid(){InitializeGrid(TArray<ACGTile*>());};

	UFUNCTION()
	void HighlightTiles(ETileType TileType);
	
	UFUNCTION()
	void InitializeGrid(TArray<ACGTile*> FileTileArray);

	UFUNCTION()
	ACGTile* GetTile(int32 i, int32 j);

	UFUNCTION(CallInEditor, Category = "CG|Events")
	void BlueprintEditorTick(float DeltaTime);

	UFUNCTION(CallInEditor, Category = "CG|Events")
	void LoadTileArrayFromFile();
	void LoadRandomTileArrayFromFile();

	UFUNCTION(CallInEditor, Category = "CG|Events")
	void SaveTileArrayToFile();

	void SaveTileArray(FArchive& Ar, TArray<ACGTile*>& ClassArray);
	void LoadTileArray(FArchive& Ar, TArray<ACGTile*>& ClassArray);
	
private:
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
protected:
	virtual void BeginPlay() override;

	virtual bool ShouldTickIfViewportsOnly() const override ;
	
public:
	virtual void Tick(float DeltaTime) override;
};
