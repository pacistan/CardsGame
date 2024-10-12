// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "CGTileObjectBase.generated.h"

struct FGameplayTag;
class ACGTile;
/**
 *  Base class for all the objects that can be placed on a tile
 */
UCLASS(Abstract, BlueprintType, DisplayName = "Tile Object")
class CARDGAME_API ACGTileObjectBase : public AActor
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FGameplayTag ObjectType;
	
	// The tile that owns this object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACGTile* TileOwner;

	// The player that Had Spawned this object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APawn* PLayerOwner;
	/* ------------------------------------------ METHODS -------------------------------------------*/
public:
	ACGTileObjectBase(const FObjectInitializer& ObjectInitializer);

	/* Function Call when the Object is Spawn on a Tile */
	UFUNCTION()
	virtual void OnSpawned(ACGTile* lTileOwner, APawn* Player);

	UFUNCTION()
	virtual void DestroyObject(APawn* Player, ACGTileObjectBase* ObjectInstigator = nullptr);
	
	/* ------------------------------------------ Override -------------------------------------------*/
};
