#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CGGridManager.generated.h"

class ACGTile;
class ACGGameMode;

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

	TArray<TArray<TObjectPtr<ACGTile>>> GridTiles;

	UPROPERTY(EditDefaultsOnly, Category = "GM/GridManager")
	bool UseEditorTick;

public:
	TArray<TArray<TObjectPtr<ACGTile>>> GetTiles() const {return GridTiles;};
	
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
};
