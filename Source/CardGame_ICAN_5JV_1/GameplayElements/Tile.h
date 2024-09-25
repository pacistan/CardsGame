// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

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
	
protected:
	void SetRow(const int32& row) {m_Row = row;};

	void SetColumn(const int32& column) {m_Column = column;};

	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
public:
	ATile();

private:
	UFUNCTION(CallInEditor)
	void BlueprintEditorTick(float DeltaTime);
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual bool ShouldTickIfViewportsOnly() const override;
	
public:
	virtual void Tick(float DeltaTime) override;


};
