#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridManager.generated.h"

class ATile;
class AGameMode_Gameplay;

USTRUCT(BlueprintType)
struct FTileArray
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<ATile>> NestedTileArray;
};

UCLASS()
class CARDGAME_ICAN_5JV_1_API AGridManager : public AActor
{
	GENERATED_BODY()

	/* ------------------------------------------ MEMBERS -------------------------------------------*/
private:
	UPROPERTY(EditDefaultsOnly, Category = "GM/Grid Generation Parameters")
	int32 m_RowNum;

	UPROPERTY(EditDefaultsOnly, Category = "GM/Grid Generation Parameters")
	int32 m_ColumnNum;

	UPROPERTY(EditDefaultsOnly, Category = "GM/Grid Generation Parameters")
	double m_TileWidth;

	UPROPERTY(EditDefaultsOnly, Category = "GM/Grid Generation Parameters")
	double m_TileSpacing;
	
	UPROPERTY(EditDefaultsOnly, Category = "GM/Grid Generation References")
	TSubclassOf<ATile> m_TileBP;

	UPROPERTY(Getter(GetTiles))
	TArray<FTileArray> m_GridTiles;

	UPROPERTY(EditDefaultsOnly, Category = "GM/GridManager")
	bool m_UseEditorTick;

public:
	UFUNCTION()
	const TArray<FTileArray>& GetTiles() const {return m_GridTiles;};
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
public:
	AGridManager();

	UFUNCTION(CallInEditor, Category = "GM/GridManager")
	void InitializeGrid();

	UFUNCTION()
	ATile* GetTile(int32 i, int32 j);

	UFUNCTION(CallInEditor, Category = "Events")
	void BlueprintEditorTick(float DeltaTime);
	
private:
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
protected:
	virtual void BeginPlay() override;

	virtual bool ShouldTickIfViewportsOnly() const override ;
	
public:
	virtual void Tick(float DeltaTime) override;

	friend class AGameMode_Gameplay;
};
