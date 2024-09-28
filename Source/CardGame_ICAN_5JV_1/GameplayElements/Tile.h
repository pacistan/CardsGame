// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardGame_ICAN_5JV_1/Card/CardData/CardProperties/CardProperty_Summon.h"
#include "GameFramework/Actor.h"
#include "TileObject/TileObjectBase.h"
#include "Tile.generated.h"

class ATileObject_Object;
class ATileObject_Unit;

UCLASS()
class CARDGAME_ICAN_5JV_1_API ATile : public AActor
{
	GENERATED_BODY()
	
	friend class AGridManager;

	/* ------------------------------------------ MEMBERS -------------------------------------------*/
private:
	UPROPERTY(EditAnywhere, Category = "Tile/Map Edition")
	bool m_IsActive;

	UPROPERTY(EditAnywhere, Category = "Tile/Editor")
	bool m_UseEditorTick = true;

	UPROPERTY(EditDefaultsOnly, Category = "Tile/References")
	TSoftObjectPtr<UMaterialInterface> m_ActiveMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Tile/References")
	TSoftObjectPtr<UMaterialInterface> m_InactiveMaterial;

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> m_MeshComponent;
	
	UPROPERTY()
	bool m_IsActiveChecker = true;
	
	UPROPERTY()
	int32 m_Row;

	UPROPERTY()
	int32 m_Column;

	UPROPERTY(VisibleInstanceOnly, Category = "Tile/Runtime")
	bool bIsOccupied = false;

	UPROPERTY(VisibleInstanceOnly, Category = "Tile/Runtime/Objects")
	ATileObject_Unit* m_Unit;

	UPROPERTY(VisibleInstanceOnly, Category = "Tile/Runtime/Objects")
	TArray<ATileObject_Object*> m_Objects;
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
public:
	ATile();
	
	UFUNCTION(BlueprintCallable)
	bool CanSummonOnTile(APawn* Player) const;

	UFUNCTION(BlueprintCallable)
	bool CanPlaceObjectOnTile(APawn* Player) const;
	
	UFUNCTION(BlueprintCallable)
	bool CanMoveOnTile(ATileObject_Unit* Unit, APawn* Player) const;

	UFUNCTION(BlueprintCallable)
	bool SummonOnTile(TSubclassOf<ATileObject_Unit> Class, APawn* Player);

	UFUNCTION(BlueprintCallable)
	bool PlaceObjectOnTile(TSubclassOf<ATileObject_Object> Class, APawn* Player);
	
private:
	UFUNCTION(CallInEditor)
	void BlueprintEditorTick(float DeltaTime);
	
protected:
	void SetRow(const int32& row) {m_Row = row;};

	void SetColumn(const int32& column) {m_Column = column;};

public:
	const int32 GetRow() const {return m_Row;};
	const int32 GetColumn() const {return m_Column;};
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual bool ShouldTickIfViewportsOnly() const override;
	
public:
	virtual void Tick(float DeltaTime) override;
	
};
