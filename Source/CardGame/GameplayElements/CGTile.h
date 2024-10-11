// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardGame/Card/CardData/CardProperties/CGCardProperty_Summon.h"
#include "GameFramework/Actor.h"
#include "CGTile.generated.h"

class ACGTileObject_SpellItem;
class ACGTileObject_Unit;

UCLASS()
class CARDGAME_API ACGTile : public AActor
{
	GENERATED_BODY()
	
	friend class ACGGridManager;

	/* ------------------------------------------ MEMBERS -------------------------------------------*/
private:
	UPROPERTY(EditAnywhere, Category = "Tile/Map Edition")
	bool IsActive;

	UPROPERTY(EditAnywhere, Category = "Tile/Editor")
	bool bUseEditorTick = true;

	UPROPERTY(EditDefaultsOnly, Category = "Tile/References")
	TSoftObjectPtr<UMaterialInterface> ActiveMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Tile/References")
	TSoftObjectPtr<UMaterialInterface> InactiveMaterial;

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY()
	bool IsActiveChecker = true;
	
	UPROPERTY()
	int32 Row;

	UPROPERTY()
	int32 Column;

	UPROPERTY(VisibleInstanceOnly, Category = "Tile/Runtime")
	bool bIsOccupied = false;

	UPROPERTY(VisibleInstanceOnly, Category = "Tile/Runtime/Objects")
	ACGTileObject_Unit* Unit;

	UPROPERTY(VisibleInstanceOnly, Category = "Tile/Runtime/Objects")
	TArray<ACGTileObject_SpellItem*> Objects;
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
public:
	ACGTile();
	
	UFUNCTION(BlueprintCallable)
	bool CanSummonOnTile(APawn* Player) const;

	UFUNCTION(BlueprintCallable)
	bool CanPlaceObjectOnTile(APawn* Player) const;
	
	UFUNCTION(BlueprintCallable)
	bool CanMoveOnTile(ACGTileObject_Unit* lUnit, APawn* Player) const;

	UFUNCTION(BlueprintCallable)
	bool SummonOnTile(TSubclassOf<ACGTileObject_Unit> Class, APawn* Player);

	UFUNCTION(BlueprintCallable)
	bool PlaceObjectOnTile(TSubclassOf<ACGTileObject_SpellItem> Class, APawn* Player);
	
private:
	UFUNCTION(CallInEditor)
	void BlueprintEditorTick(float DeltaTime);
	
protected:
	void SetRow(const int32& row) {Row = row;};
	void SetColumn(const int32& column) {Column = column;};

public:
	int32 GetRow() const {return Row;};
	int32 GetColumn() const {return Column;};
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual bool ShouldTickIfViewportsOnly() const override;
	
public:
	virtual void Tick(float DeltaTime) override;
	
};
