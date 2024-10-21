// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardGame/Card/CardData/CardProperties/CGCardProperty_Summon.h"
#include "CardGame/Interfaces/Hoverable.h"
#include "GameFramework/Actor.h"
#include "CGTile.generated.h"

class ACGTileObject_SpellItem;
class ACGTileObject_Unit;

UENUM()
enum class ETileType : uint32 { Disabled, Normal, Player1, Player2, Player3, Player4 };

UCLASS()
class CARDGAME_API ACGTile : public AActor, public IHoverable, public ISelectable, public IExaminable
{
	GENERATED_BODY()
	
	friend class ACGGridManager;

	/* ------------------------------------------ MEMBERS -------------------------------------------*/
private:
	UPROPERTY(EditAnywhere, Category = "Tile/Map Edition")
	ETileType TileType = ETileType::Normal;

	UPROPERTY()
	bool IsHighlighted;

	UPROPERTY()
	bool IsHovered;
	
	UPROPERTY(EditAnywhere, Category = "Tile/Editor")
	bool bUseEditorTick = true;

	UPROPERTY(EditDefaultsOnly, Category = "Tile/References")
	TSoftObjectPtr<UMaterialInterface> ActiveMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Tile/References")
	TSoftObjectPtr<UMaterialInterface> InactiveMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Tile/References")
	TSoftObjectPtr<UMaterialInterface> HighlightMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Tile/References")
	TSoftObjectPtr<UMaterialInterface> HoveredMaterial;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tile/References")
	TSoftObjectPtr<UMaterialInterface> PlayerMaterial;

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY()
	ETileType PreviousTileType = ETileType::Normal;
	
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
	bool CanSummonOnTile(ACG_PlayerPawn* Player) const;

	UFUNCTION(BlueprintCallable)
	bool CanPlaceObjectOnTile(ACG_PlayerPawn* Player) const;
	
	UFUNCTION(BlueprintCallable)
	bool CanMoveOnTile(ACGTileObject_Unit* lUnit, ACG_PlayerPawn* Player) const;

	UFUNCTION(BlueprintCallable)
	bool SummonOnTile(TSubclassOf<ACGTileObjectBase> Class, ACG_PlayerPawn* Player);

	UFUNCTION(BlueprintCallable)
	bool PlaceObjectOnTile(TSubclassOf<ACGTileObject_SpellItem> Class, ACG_PlayerPawn* Player);
	
private:
	UFUNCTION(CallInEditor)
	void BlueprintEditorTick(float DeltaTime);

	void UpdateMaterial();
	
protected:
	void SetRow(const int32& row) {Row = row;};
	void SetColumn(const int32& column) {Column = column;};
	void SetTileType(const ETileType& newTileType) {TileType = newTileType;};

public:
	int32 GetRow() const {return Row;};
	int32 GetColumn() const {return Column;};

	UFUNCTION()
	void SetHighlighted();
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual bool ShouldTickIfViewportsOnly() const override;
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnHoverStart(ACG_PlayerPawn* Pawn) override;

	virtual void OnHoverStop(ACG_PlayerPawn* Pawn)  override;
	
	virtual void OnSelect(ACG_PlayerPawn* Pawn)  override
	{
		if(IsHighlighted && IsHovered)
		{
			Pawn->PlayCard(this);
			//TODO: Apply Effect Card From Pawn
		}
		
	}

	virtual void OnRelease(ACG_PlayerPawn* Pawn) override{}

	virtual void OnExamine(ACG_PlayerPawn* Pawn) override{}
};
