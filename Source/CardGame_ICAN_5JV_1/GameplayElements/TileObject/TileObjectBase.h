// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "GameFramework/Actor.h"
#include "TileObjectBase.generated.h"

struct FGameplayTag;
class ATile;
/**
 *  Base class for all the objects that can be placed on a tile
 */
UCLASS(Abstract, BlueprintType, DisplayName = "Tile Object")
class CARDGAME_ICAN_5JV_1_API ATileObjectBase : public AActor
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString m_ObjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> m_Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FGameplayTag m_ObjectType;
	
	// The tile that owns this object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ATile* m_TileOwner;

	// The player that Had Spawned this object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APawn* m_PLayerOwner;
	/* ------------------------------------------ METHODS -------------------------------------------*/
public:
	ATileObjectBase(const FObjectInitializer& ObjectInitializer);

	/* Function Call when the Object is Spawn on a Tile */
	UFUNCTION()
	virtual void OnSpawned(ATile* TileOwner, APawn* Player);

	UFUNCTION()
	virtual void DestroyObject(APawn* Player, ATileObjectBase* ObjectInstigator = nullptr);
	
	/* ------------------------------------------ Override -------------------------------------------*/
};
