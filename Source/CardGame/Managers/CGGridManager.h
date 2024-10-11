#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CGGridManager.generated.h"

class ACGTile;
class ACGGameMode;

USTRUCT(BlueprintType)
struct FTileArray
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<ACGTile>> NestedTileArray;
};

UCLASS()
class CARDGAME_API ACGGridManager : public AActor
{
	GENERATED_BODY()

	/* ------------------------------------------ MEMBERS -------------------------------------------*/
private:
	UPROPERTY(EditDefaultsOnly, Category = "GM/Grid Generation Parameters")
	int32 RowNum;

	UPROPERTY(EditDefaultsOnly, Category = "GM/Grid Generation Parameters")
	int32 ColumnNum;

	UPROPERTY(EditDefaultsOnly, Category = "GM/Grid Generation Parameters")
	double TileWidth;

	UPROPERTY(EditDefaultsOnly, Category = "GM/Grid Generation Parameters")
	double TileSpacing;
	
	UPROPERTY(EditDefaultsOnly, Category = "GM/Grid Generation References")
	TSubclassOf<ACGTile> TileBP;

	UPROPERTY(Getter(GetTiles))
	TArray<FTileArray> GridTiles;

	UPROPERTY(EditDefaultsOnly, Category = "GM/GridManager")
	bool UseEditorTick;

public:
	UFUNCTION()
	const TArray<FTileArray>& GetTiles() const {return GridTiles;};
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
public:
	ACGGridManager();

	UFUNCTION(CallInEditor, Category = "GM/GridManager")
	void InitializeGrid();

	UFUNCTION()
	ACGTile* GetTile(int32 i, int32 j);

	UFUNCTION(CallInEditor, Category = "Events")
	void BlueprintEditorTick(float DeltaTime);
	
private:
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
protected:
	virtual void BeginPlay() override;

	virtual bool ShouldTickIfViewportsOnly() const override ;
	
public:
	virtual void Tick(float DeltaTime) override;

	friend class ACGGameMode;
};
