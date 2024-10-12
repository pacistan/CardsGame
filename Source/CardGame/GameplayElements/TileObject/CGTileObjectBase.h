// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorPickerMode.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "CGTileObjectBase.generated.h"

struct FGameplayTag;
class ACGTile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTileObjectBaseDelegate);

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
	
public:
	/* Delegate call When the Object kill a Unit */
	UPROPERTY()
	FTileObjectBaseDelegate OnKillDelegate;

	/* Delegate call When the Object Move */
	UPROPERTY()
	FTileObjectBaseDelegate OnMoveDelegate;

	/* Delegate call On the Object Death */
	UPROPERTY()
	FTileObjectBaseDelegate OnDeathDelegate;

	/* Delegate call On the Object Spawn */
	UPROPERTY()
	FTileObjectBaseDelegate OnSpawnDelegate;
	
	/* ------------------------------------------ METHODS -------------------------------------------*/
public:
	ACGTileObjectBase(const FObjectInitializer& ObjectInitializer);
	
	/* Function To Call when the Object Is Initialized */
	UFUNCTION()
	virtual void Initialize(ACGTile* lOwner, APawn* player);
	
	/* Function Call for Destroy the Object */
	UFUNCTION()
	virtual void DestroyObject(APawn* player, ACGTileObjectBase* objectInstigator = nullptr);

	/* Function Call when the Object is Selected */
	UFUNCTION()
	virtual void OnSelected(APawn* player); 
	
protected:
	/* Function Call when the Object kill a unit */
	UFUNCTION()
	virtual void OnKill() { OnKillDelegate.Broadcast(); };

	/* Function Call when the Object Move */
	UFUNCTION()
	virtual void OnMove() { OnMoveDelegate.Broadcast(); };

	/* Function Call when the Object Die */
	UFUNCTION()
	virtual void OnDeath() { OnDeathDelegate.Broadcast(); };

	/* Function Call when the Object Spawn */
	UFUNCTION()
	virtual void OnSpawn() { OnSpawnDelegate.Broadcast(); };
	
	/* ------------------------------------------ Override -------------------------------------------*/
};
